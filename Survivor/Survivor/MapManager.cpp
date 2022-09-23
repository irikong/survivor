#include "MapManager.h"
#include "TileMapComponent.h"
#include "Constants.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "BoxComponent.h"
#include <queue>

MapManager::MapManager(Game* game) :
	Actor(game)
{
	SetLayer(EProp);

	Renderer* renderer = GetGame()->GetRenderer();
	float fWidth = 32, fHeight = 32;
	float mapRow = 16, mapCol = 16;
	mMap = std::vector<std::vector<int>>(mapRow, std::vector<int>(mapCol, 1));
	mMapRow = mapRow;
	mMapCol = mapCol;
	mMapWidth = fWidth * mapRow;
	mMapHeight = fHeight * mapCol;
	mPixelOffset.x = mMapWidth / 2;
	mPixelOffset.y = -mMapHeight / 2;

	SetPosition(Vector2(-(fWidth * mapRow - fWidth) / 2, (fHeight * mapCol - fHeight) / 2));

	TileMapComponent* tm1 = new TileMapComponent(this, 32, 32);
	tm1->SetTexture(renderer->GetTexture("Grass1.png"));
	tm1->LoadTileMap(std::string(Path::ASSETS) + "Grass.csv", 16, 16);
	TileMapComponent* tm2 = new TileMapComponent(this, 32, 32);
	tm2->SetTexture(renderer->GetTexture("Dirt2.png"));
	tm2->LoadTileMap(std::string(Path::ASSETS) + "Dirt.csv", 16, 16);
	TileMapComponent* tm3 = new TileMapComponent(this, 32, 32);
	tm3->SetTexture(renderer->GetTexture("Water2.png"));
	tm3->LoadTileMap(std::string(Path::ASSETS) + "Water.csv", 16, 16);
	tm3->UpdateUnwalkable(mMap);

	//MakeWall(fWidth, fHeight, mapRow, mapCol);
	MakeLight();
}

bool MapManager::IsGround(const Vector2& pos)
{
	Vector2 pixelPos = WorldToPixel(pos);
	
	return 0 < pixelPos.x && pixelPos.x < mMapWidth && 0 < pixelPos.y && pixelPos.y < mMapHeight && mMap[pixelPos.y / 32][pixelPos.x / 32];
}

Vector2 MapManager::WorldToPixel(const Vector2& worldPos)
{
	return Vector2((mPixelOffset.x + worldPos.x), -(mPixelOffset.y + worldPos.y));
}

bool MapManager::PathFinding(int sr, int sc, int fr, int fc) // A* search
{
	if (!(0 <= sr && sr < mMapRow && 0 <= sc && sc < mMapCol && mMap[sr][sc])) return false;
	if (!(0 <= fr && fr < mMapRow && 0 <= fc && fc < mMapCol && mMap[fr][fc])) return false;
	
	std::vector<std::vector<Cell>> cellMap(mMapRow, std::vector<Cell>(mMapCol));
	std::priority_queue<Cell*, std::vector<Cell*>, Cell> openList;

	int dr[4] = { -1, 0, 1, 0 };
	int dc[4] = { 0, 1, 0, -1 };

	cellMap[sr][sc].f = cellMap[sr][sc].g = cellMap[sr][sc].h = 0;
	cellMap[sr][sc].r = sr;
	cellMap[sr][sc].c = sc;
	cellMap[sr][sc].parentR = sr;
	cellMap[sr][sc].parentC = sc;
	openList.push(&cellMap[sr][sc]);

	while (!openList.empty()) {
		Cell* curr = openList.top();
		int r = curr->r;
		int c = curr->c;
		openList.pop();

		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (0 <= nr && nr < mMapRow && 0 <= nc && nc < mMapCol && mMap[nr][nc] && !cellMap[nr][nc].isClosed) {
				if (nr == fr && nc == fc) {
					cellMap[nr][nc].parentR = r;
					cellMap[nr][nc].parentC = c;
					return true;
				}
				
				int ng = curr->g + 1;
				int nh = CalcHeuristic(nr, nc, fr, fc);
				int nf = ng + nh;

				if ((cellMap[nr][nc].f == Math::INF) || (nf < cellMap[nr][nc].f)) {
					cellMap[nr][nc].f = nf;
					cellMap[nr][nc].g = ng;
					cellMap[nr][nc].h = nh;
					cellMap[nr][nc].r = nr;
					cellMap[nr][nc].c = nc;
					cellMap[nr][nc].parentR = r;
					cellMap[nr][nc].parentC = c;
					openList.push(&cellMap[nr][nc]);
				}
			}
		}
	}

	return false;
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

	renderer->SetAmbientLight(Vector3(1.0f, 1.0f, 1.0f));

	//PointLight* pt = new PointLight{ Vector3(40, 10, 0), Vector3(1, 1, 1), 50 };
	//renderer->AddPointLight(pt);
	//pt = new PointLight{ Vector3(-100, -100, 0), Vector3(1, 1, 1), 100 };
	//renderer->AddPointLight(pt);
}

int MapManager::CalcHeuristic(int r, int c, int fr, int fc)
{
	return Math::Abs(fr - r) + Math::Abs(fc - c);
}
