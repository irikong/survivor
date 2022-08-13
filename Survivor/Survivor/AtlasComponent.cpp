#include "AtlasComponent.h"

AtlasComponent::AtlasComponent(Actor* owner, int drawOrder) :
	SpriteComponent(owner, drawOrder),
	FRAME_WIDTH(),
	FRAME_HEIGHT(),
	FRAMES_PER_ROW(),
	FRAMES_PER_COL()
{

}

void AtlasComponent::Draw(Shader* shader)
{
}

void AtlasComponent::SetFrameInfo(int fWidth, int fHeight, int fPerRow, int fPerCol)
{
	FRAME_WIDTH = fWidth;
	FRAME_HEIGHT = fHeight;
	FRAMES_PER_ROW = fPerRow;
	FRAMES_PER_COL = fPerCol;
}

std::pair<int, int> AtlasComponent::GetFrameCoord(int frame)
{
	return { FRAME_WIDTH * (frame % FRAMES_PER_ROW), FRAME_HEIGHT * (frame / FRAMES_PER_COL) }; // LU
}
