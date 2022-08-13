#include "AtlasComponent.h"

AtlasComponent::AtlasComponent(Actor* owner, int fWidth, int fHeight, int drawOrder) :
	SpriteComponent(owner, drawOrder),
	FRAME_WIDTH(fWidth),
	FRAME_HEIGHT(fHeight),
	FRAMES_PER_ROW(),
	FRAMES_PER_COL()
{

}

void AtlasComponent::Draw(Shader* shader)
{
}

void AtlasComponent::SetTexture(Texture* texture)
{
	SpriteComponent::SetTexture(texture);

	FRAMES_PER_ROW = mTexWidth / FRAME_WIDTH;
	FRAMES_PER_COL = mTexHeight / FRAME_HEIGHT;
}

void AtlasComponent::SetFrameInfo(int fWidth, int fHeight)
{
	FRAME_WIDTH = fWidth;
	FRAME_HEIGHT = fHeight;
}

std::pair<int, int> AtlasComponent::GetFrameCoord(int frame)
{
	return { FRAME_WIDTH * (frame % FRAMES_PER_ROW), FRAME_HEIGHT * (frame / FRAMES_PER_COL) }; // LU
}
