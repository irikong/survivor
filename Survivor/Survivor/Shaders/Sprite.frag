#version 330

uniform sampler2D uTexture;
uniform float uAlpha;

uniform vec3 uAmbientLight;

in vec2 fragUV;

out vec4 outColor;

void main()
{
    vec3 light = uAmbientLight;
    outColor = texture(uTexture, fragUV) * vec4(light, uAlpha);
}
