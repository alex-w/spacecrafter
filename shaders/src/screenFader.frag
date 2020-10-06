//
//	screen_fader
//
#version 420
#pragma debug(on)
#pragma optimize(off)

layout (binding=0) uniform ubo {float intensity;};

layout (location=0) out vec4 FragColor;
 
void main(void)
{
	FragColor = vec4(0.0,0.0,0.0,intensity);
}
