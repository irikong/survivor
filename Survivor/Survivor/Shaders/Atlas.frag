#version 330

uniform sampler2D uTexture;
uniform int uIdx;
uniform int uTPR; // TILES_PER_ROW
uniform int uTPC; // TILES_PER_COL
uniform float uAlpha;

in vec2 fragUV;

out vec4 outColor;

void main()
{
    vec2 newUV = vec2((fragUV.x + mod(uIdx, uTPR)) / uTPR, (fragUV.y + uIdx / uTPR) / uTPC);
    outColor = texture(uTexture, newUV) * vec4(1.0, 1.0, 1.0, uAlpha);
}
