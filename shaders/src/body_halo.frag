//
//	body_halo
//
#version 420
#pragma debug(on)
#pragma optimize(off)

//externe
layout(binding=0, set=1) uniform sampler2D mapTexture;

//in
layout(location=0) in vec2 TexCoord;
layout(location=1) in vec3 Color;

//out
layout(location=0) out vec3 FragColor;

void main(void)
{
	FragColor = vec3(texture(mapTexture,TexCoord)) * Color;
}

