#pragma once
#include "AtlasComponent.h"
#include <vector>
#include <string>

class TileMapComponent : public AtlasComponent
{
public:
	TileMapComponent(class Actor* owner, int fWidth, int fHeight, int drawOrder = 10);
	~TileMapComponent() = default;

	void Draw(class Shader* shader) override;
	void LoadTileMap(const std::string& filePath, int mapRow, int mapCol);

	Type GetType() const override { return kTileMapComponent; }

private:
	struct Tile {
		int texIdx;
		int posX, posY;

		Tile(int _idx, int _x, int _y) : texIdx(_idx), posX(_x), posY(_y) {}
	};
	std::vector<Tile> mTiles;

	// MAP INFO
	int MAP_ROW;
	int MAP_COL;
};

