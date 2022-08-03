#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inUV;

out vec2 fragUV;

void main()
{
	vec4 pos = vec4(inPos, 1.0);
	gl_Position = pos * uWorldTransform * uViewProj;

	fragUV = inUV;
}
