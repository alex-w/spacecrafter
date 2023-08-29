//
// Moon shadow
//

#version 430
#pragma debug(on)
#pragma optimize(off)
#pragma optionNV(fastprecision off)

#include <cam_block.glsl>

layout (binding=2) uniform sampler2D heightMap;
layout (binding=3) uniform sampler2D normalMap;
layout (binding=4) uniform sampler2D dayTexture;
layout (binding=5) uniform sampler2DArray bodyShadows;

#define M_PI 3.14159265358979323846

struct ShadowingBody {
    vec2 pos;
    float size;
    int idx;
};

layout (binding=1) uniform globalFrag {
	mat3 ShadowMatrix;
	vec3 lightDirection; // In body-local coordinates
	float sinSunAngle;
	float heightMapDepthLevel; // 0.9
	float heightMapDepth; // 0.1
	float squaredHeightMapDepthLevel; // 0.81
	float sunDeviation; // Deviation of the sun ray
	float atmDeviation; // Deviation of the atmosphere color
	vec3 atmColor; // Colorimetry of the atmosphere
	int nbShadowingBodies;
	ShadowingBody shadowingBodies[4];
};

layout (location=0) in vec3 entryPos;
layout (location=1) in vec3 viewDirection;
layout (location=2) in flat float side;

layout (location=0) out vec4 fragColor;

// sin(x) = sqrt(1 - cos(x)²)
// sin(x) * (1 - cos(x))
// sqrt(1 - cos(x)²) * (1 - cos(x))

#define UNIT_STEP_COUNT 1024
#define STEP_COUNT 24
#define SHADOW_STEP_FACTOR 1.1
#define SHADOW_STEP_INIT (1.f/8192)
#define SHADOW_MIN_STEP (1.f/65536)

float xyzToHeight(vec3 pos)
{
	float depth = length(pos);
	float tmp = atan(pos.y, pos.x) / (2 * M_PI);
	tmp += mix(0.5, 1.5, tmp < side);
	return (depth - heightMapDepthLevel) / heightMapDepth - textureLod(heightMap, vec2(
		tmp,
		acos(-pos.z/depth) / M_PI
	), 0).r;
}

void main(void)
{
	vec3 view = normalize(viewDirection);
	vec3 samplePos = normalize(entryPos);
	float rayLength = -dot(view, samplePos);
	float delta = squaredHeightMapDepthLevel - (1 - rayLength*rayLength);
	bool hitBody = (delta > 0);
	if (hitBody)
		rayLength = rayLength - sqrt(delta);
	int stepCount = int(rayLength * UNIT_STEP_COUNT);
	vec3 rayStep = view * (rayLength / stepCount);
	for (int i = 0; i < stepCount; ++i) {
		samplePos += rayStep;
		if (xyzToHeight(samplePos) < 0) {
			hitBody = true;
			rayStep /= 2;
			samplePos -= rayStep;
			break;
		}
	}
	vec3 color = vec3(0);
	if (hitBody) {
		for (int i = 0; i < STEP_COUNT; ++i) {
			rayStep /= 2;
			if (xyzToHeight(samplePos) < 0) {
				samplePos -= rayStep; // Ground hit
			} else {
				samplePos += rayStep;
			}
		}
		float tmp = atan(samplePos.y, samplePos.x) / (2 * M_PI);
		tmp += mix(0.5, 1.5, tmp < side);
		float depth = length(samplePos);
		vec2 texCoord = vec2(tmp, acos(-samplePos.z/depth) / M_PI);
		vec2 shadowPos = vec2(ShadowMatrix * samplePos); // For shadow projection
		vec3 xAxis = normalize(vec3(-samplePos.y, samplePos.x, 0));
		samplePos /= depth;
		vec3 yAxis = normalize(cross(xAxis, samplePos));
		if (yAxis.z < 0)
			yAxis = -yAxis;
		vec3 normal = normalize(mat3(xAxis,yAxis, samplePos) * (texture(normalMap, texCoord).xyz * 2 - 1));
		vec3 sunDirection = normalize(samplePos * sunDeviation - lightDirection);
		float NdotL = clamp(dot(sunDirection, normal) + ambient, ambient, 1);
		float atmosphere = clamp(atmDeviation - dot(lightDirection, samplePos), 0, 1);
		samplePos *= textureLod(heightMap, texCoord, 0).r * heightMapDepth + heightMapDepthLevel;
		if (NdotL + atmosphere > ambient) {
			float shadowing = 1;
			// Process shadow of bodies
			for (int i = 0; i < nbShadowingBodies; ++i) {
				vec2 tmp = (shadowPos.xy - shadowingBodies[i].pos) / shadowingBodies[i].size;
				if (dot(tmp, tmp) < 1) {
					shadowing *= 1 - texture(bodyShadows, vec3(tmp * 0.5 + 0.5, shadowingBodies[i].idx)).r;
				}
			}
			// shortly ray trace toward -lightDirection for self-shadowing
			rayLength = SHADOW_STEP_INIT;
			float maxOcclusion = 1;
			float tmp;
			float prev = 0;
			bool approaching = false; // Is previously approaching
			do {
				tmp = xyzToHeight(samplePos + sunDirection * rayLength);
				if (tmp < prev) {
					approaching = true;
				} else if (approaching) {
					prev = rayLength / SHADOW_STEP_FACTOR;
					float tmpR = rayLength - prev;
					do {
						tmpR /= 2;
						if (xyzToHeight(samplePos + sunDirection * (prev - tmpR)) < xyzToHeight(samplePos + sunDirection * (prev + tmpR))) {
							prev -= tmpR;
						} else {
							prev += tmpR;
						}
					} while (tmpR > SHADOW_MIN_STEP);
					maxOcclusion = min(maxOcclusion, xyzToHeight(samplePos + sunDirection * prev) / prev);
					approaching = false;
				}
				prev = tmp;
				rayLength *= SHADOW_STEP_FACTOR;
			} while (tmp < 0.8);
			NdotL *= clamp(maxOcclusion * heightMapDepth / sinSunAngle + 0.5, 0, 1);

			// Process color
			color = texture(dayTexture, texCoord).xyz * min(mix(vec3(NdotL), vec3(atmosphere), atmColor) * shadowing + ambient, 1);
		} else {
			color = texture(dayTexture, texCoord).xyz * ambient;
		}
	} else {
		discard;
	}
	// Atmosphere may be traced here
	fragColor = vec4(color, 1);
}
