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
	SetLayer(EProp);

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

	MakeWall(fWidth, fHeight, mapRow, mapCol);
	MakeLight();
}

void MapManager::MakeWall(float fWidth, float fHeight, float mapRow, float mapCol)
{
	float mapWidth = fWidth * mapRow;
	float mapHeight = fHeight * mapCol;

	AABB box;
	BoxComponent* bc;
	Vector2 min, max;
	Vector2 offset(-fWidth / 2.f, fHeight / 2.f);

	// 가로
	min = Vector2(-fWidth, 0.0f) + offset;
	max = Vector2(mapWidth + fWidth, fHeight) + offset;

	box.mMin = min;
	box.mMax = max;
	bc = new BoxComponent(this, box);

	box.mMin.y -= (mapHeight + fHeight);
	box.mMax.y -= (mapHeight + fHeight);
	bc = new BoxComponent(this, box);

	// 세로
	min = Vector2(-fWidth, -(mapHeight + fHeight)) + offset;
	max = Vector2(0.0f, fHeight) + offset;

	box.mMin = min;
	box.mMax = max;
	bc = new BoxComponent(this, box);

	box.mMin.x += (mapWidth + fWidth);
	box.mMax.x += (mapWidth + fWidth);
	bc = new BoxComponent(this, box);
}

void MapManager::MakeLight()
{
	Renderer* renderer = GetGame()->GetRenderer();

	renderer->SetAmbientLight(Vector3(0.3f, 0.3f, 0.3f));

	PointLight* pt = new PointLight{ Vector3(40, 10, 0), Vector3(1, 1, 1), 50 };
	renderer->AddPointLight(pt);
	pt = new PointLight{ Vector3(-100, -100, 0), Vector3(1, 1, 1), 100 };
	renderer->AddPointLight(pt);
}
