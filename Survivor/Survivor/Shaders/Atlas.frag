#version 330

uniform sampler2D uTexture;
uniform int uIdx;
uniform int uTPR; // TILES_PER_ROW
uniform int uTPC; // TILES_PER_COL
uniform float uAlpha;

struct PointLight {
	vec3 mPosition;
	vec3 mColor;
	float mRange;
	float mFallOffRange;
};

uniform vec3 uAmbientLight;
uniform PointLight uPointLight[10];
uniform int uNumPointLight;

in vec3 fragWorldPos;
in vec2 fragUV;

out vec4 outColor;

void main()
{
    vec3 light = uAmbientLight;
	
	for(int i = 0; i < uNumPointLight; i++){
		float dist = length(uPointLight[i].mPosition - fragWorldPos);
		float range = uPointLight[i].mRange;

		if(dist < range){
			float rate = min(1.0, (range - dist) / (range - uPointLight[i].mFallOffRange));
			light += rate * uPointLight[i].mColor;
		}
	}

    vec2 newUV = vec2((fragUV.x + mod(uIdx, uTPR)) / uTPR, (fragUV.y + uIdx / uTPR) / uTPC);
    outColor = texture(uTexture, newUV) * vec4(clamp(light, 0, 1), uAlpha);
}
