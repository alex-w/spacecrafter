#version 420

layout (binding=0, set=0) uniform ubo {
	mat4 ModelViewMatrix;
	mat4 ModelViewMatrixInverse;
	vec3 clipping_fov;
	float RingScale;
	vec3 PlanetPosition;
	float PlanetRadius;
	vec3 LightDirection;
	float SunnySideUp;
};

#include <fisheye_noMV.glsl>

layout (location=0) in vec3 Position3D;
layout (location=3) in vec3 Color;

layout (location=6) in vec3 Shift;

layout (location=0) out vec3 ColorOut;
layout (location=1) out float PlanetHalfAngle;
layout (location=2) out float Separation;
layout (location=3) out float SeparationAngle;
layout (location=4) out float NdotL;

void main(void)
{
	vec3 Position = vec3(ModelViewMatrix * vec4(Position3D+Shift, 1));
	ColorOut = Color;
	PlanetHalfAngle = atan(PlanetRadius/distance(PlanetPosition, Position));
	Separation = dot(LightDirection, normalize(PlanetPosition-Position));
	SeparationAngle = acos(Separation);

	vec3 modelLight = vec3(ModelViewMatrixInverse * vec4(LightDirection,1.0));

	NdotL = clamp(16.0*dot(vec3(0.0, 0.0, 1.0-2.0*SunnySideUp), modelLight), -1.0, 1.0);

	gl_Position = fisheyeProject((Position3D+Shift)*RingScale, clipping_fov);
}
