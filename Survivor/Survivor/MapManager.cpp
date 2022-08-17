#include "MapManager.h"
#include "TileMapComponent.h"
#include "Constants.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "BoxComponent.h"
#include "Math.h"

MapManager::MapManager(Game* game) :
	Actor(game)
{
	Renderer* renderer = GetGame()->GetRenderer();
	float fWidth = 32, fHeight = 32;
	float mapRow = 16, mapCol = 16;

	SetPosition(Vector2(-(fWidth * mapRow - fWidth) / 2, (fHeight * mapCol - fHeight) / 2));

	TileMapComponent* tm1 = new TileMapComponent(this, 32, 32);
	tm1->SetTexture(renderer->GetTexture("Grass1.png"));
	tm1->LoadTileMap(std::string(Path::ASSETS) + "Layer1.csv", 16, 16);
	TileMapComponent* tm2 = new TileMapComponent(this, 32, 32);
	tm2->SetTexture(renderer->GetTexture("Dirt2.png"));
	tm2->LoadTileMap(std::string(Path::ASSETS) + "Layer2.csv", 16, 16);
}

