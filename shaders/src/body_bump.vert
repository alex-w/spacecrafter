//
// moon bump
//
#version 420
#pragma debug(on)
#pragma optimize(off)
#pragma optionNV(fastprecision off)

layout (binding=0) uniform globalVertProj {
	mat4 ModelViewMatrix;
	mat4 NormalMatrix;
	vec3 clipping_fov;
	float planetRadius;
	vec3 LightPosition;
	float planetScaledRadius;
	float planetOneMinusOblateness;
};

#include <fisheye_noMV.glsl>

//layout
layout (location=0)in vec3 position;
layout (location=1)in vec2 texcoord;
layout (location=2)in vec3 normal;

#include <cam_block.glsl>

//out
layout (location=0) out vec2 TexCoord;
layout (location=1) out float Ambient;

layout (location=2) out vec3 Normal;
layout (location=3) out vec3 Position;
layout (location=4) out vec3 TangentLight;
layout (location=5) out vec3 Light;

void main()
{
	//glPosition
	vec3 Position0;
	Position0.x =position.x * planetScaledRadius;
	Position0.y =position.y * planetScaledRadius;
	Position0.z =position.z * planetScaledRadius * planetOneMinusOblateness;
	gl_Position = fisheyeProject(Position0, clipping_fov);

    //Light
	vec3 positionL = planetRadius * position ;
	positionL.z = positionL.z * planetOneMinusOblateness;
	Position = vec3(ModelViewMatrix * vec4(positionL,1.0));  
	Light = normalize(LightPosition - Position);

	//Other
	Normal = normalize(mat3(NormalMatrix) * normal);
	vec3 binormal = vec3(0,-Normal.z,Normal.y);
	vec3 tangent = cross(Normal,binormal);
	TangentLight = vec3(dot(Light, tangent), dot(Light, binormal), dot(Light, Normal)); 
    TexCoord = texcoord;
    Ambient = ambient;
}
