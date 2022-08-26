#version 330

uniform sampler2D uTexture;
uniform int uIdx;
uniform int uTPR; // TILES_PER_ROW
uniform int uTPC; // TILES_PER_COL
uniform float uAlpha;

struct PointLight {
	vec3 mPosition;
	vec3 mColor;
	float mFallOffRange;
};

uniform vec3 uAmbientLight;
uniform PointLight uPointLight;

in vec3 fragWorldPos;
in vec2 fragUV;

out vec4 outColor;

void main()
{
    vec3 light = uAmbientLight;
	float dist = length(uPointLight.mPosition - fragWorldPos);
	if(dist < uPointLight.mFallOffRange){
		light += vec3(uPointLight.mColor);
	}

    vec2 newUV = vec2((fragUV.x + mod(uIdx, uTPR)) / uTPR, (fragUV.y + uIdx / uTPR) / uTPC);
    outColor = texture(uTexture, newUV) * vec4(clamp(light, 0, 1), uAlpha);
}
