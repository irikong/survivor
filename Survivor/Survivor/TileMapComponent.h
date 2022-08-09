#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <string>

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int drawOrder = 10);
	~TileMapComponent();

	void Draw(class Shader* shader) override;
	void LoadTileMap(const std::string& filePath);
	void SetTileInfo(int tWidth, int tHeight, int tPerRow, int tPerCol);
	void SetMapInfo(int mapRow, int mapCol);

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
	// TILES INFO
	int TILE_WIDTH;
	int TILE_HEIGHT;
	int TILES_PER_ROW;
	int TILES_PER_COL;
};

