#pragma once
#include "SpriteComponent.h"
#include "unordered_map"

class AtlasComponent : public SpriteComponent
{
public:
	AtlasComponent(class Actor* owner, int drawOrder = 100);
	~AtlasComponent() = default;

	void Draw(class Shader* shader) override;

	Type GetType() const override { return kAtlasComponent; }
	void SetFrameInfo(int fWidth, int fHeight, int fPerRow, int fPerCol);
	std::pair<int, int> GetFrameCoord(int frame);

protected:
	int FRAME_WIDTH;
	int FRAME_HEIGHT;
	int FRAMES_PER_ROW;
	int FRAMES_PER_COL;
};

