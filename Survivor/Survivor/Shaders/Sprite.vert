#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inUV;

out vec3 fragWorldPos;
out vec2 fragUV;

void main()
{
	vec4 worldPos = vec4(inPos, 1.0) * uWorldTransform;
	gl_Position = worldPos * uViewProj;

	fragWorldPos = worldPos.xyz;
	fragUV = inUV;
}
