#include "MapManager.h"
#include "TileMapComponent.h"
#include "Constants.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "BoxComponent.h"
#include <queue>
#include <iostream>

MapManager::MapManager(Game* game) :
	Actor(game),
	DAY_CYCLE(120),
	mTime(DAY_CYCLE / 4)
{
	SetLayer(EProp);

	Renderer* renderer = GetGame()->GetRenderer();
	int fWidth = 32, fHeight = 32;
	int mapRow = 24, mapCol = 24;
	mMap = std::vector<std::vector<int>>(mapRow, std::vector<int>(mapCol, Math::INF));
	mTileWidth = fWidth;
	mTileHeight = fHeight;
	mMapRow = mapRow;
	mMapCol = mapCol;
	mMapWidth = static_cast<float>(fWidth * mapRow);
	mMapHeight = static_cast<float>(fHeight * mapCol);
	mPixelOffset.x = mMapWidth / 2;
	mPixelOffset.y = -mMapHeight / 2;

	SetPosition(Vector2(-(fWidth * mapRow - fWidth) / 2, (fHeight * mapCol - fHeight) / 2));

	TileMapComponent* tm1 = new TileMapComponent(this, fWidth, fHeight);
	tm1->SetTexture(renderer->GetTexture("Grass1.png"));
	tm1->LoadTileMap(std::string(Path::ASSETS) + "Grass24.csv", mapRow, mapCol);
	TileMapComponent* tm2 = new TileMapComponent(this, fWidth, fHeight);
	tm2->SetTexture(renderer->GetTexture("Dirt2.png"));
	tm2->LoadTileMap(std::string(Path::ASSETS) + "Dirt24.csv", mapRow, mapCol);
	TileMapComponent* tm3 = new TileMapComponent(this, fWidth, fHeight);
	tm3->SetTexture(renderer->GetTexture("Water2.png"));
	tm3->LoadTileMap(std::string(Path::ASSETS) + "Water24.csv", mapRow, mapCol);
	tm3->UpdateUnwalkable(mMap);

	SetDaylight(Vector3(1.f, 1.f, 1.f));
}

void MapManager::UpdateActor(float deltaTime)
{
	mTime += deltaTime;
	UpdateDaylight();
}

Vector2 MapManager::WorldToPixel(const Vector2& worldPos)
{
	return Vector2((mPixelOffset.x + worldPos.x), -(mPixelOffset.y + worldPos.y));
}

Vector2 MapManager::PixelToWorld(const Vector2& pixelPos)
{
	return Vector2((pixelPos.x - mPixelOffset.x), -(pixelPos.y + mPixelOffset.y));
}

bool MapManager::IsGround(const Vector2& worldPos)
{
	std::pair<int, int> rowCol = GetRowCol(worldPos);

	return IsValidCell(rowCol.first, rowCol.second);
}

void MapManager::ResetMap()
{
	for (int r = 0; r < mMapRow; r++) {
		for (int c = 0; c < mMapCol; c++) {
			if (mMap[r][c] != -1) mMap[r][c] = Math::INF;
		}
	}
}

bool MapManager::PathFinding(const Vector2& src, const Vector2& dst) // A* search
{
	std::pair<int, int> rowCol = GetRowCol(src);
	int srcR = rowCol.first, srcC = rowCol.second;
	rowCol = GetRowCol(dst);
	int dstR = rowCol.first, dstC = rowCol.second;

	if (!IsValidCell(srcR, srcC)) return false;
	if (!IsValidCell(dstR, dstC)) return false;
	if (mMap[srcR][srcC] != Math::INF) {
		return true;
	}
	
	std::vector<std::vector<Cell>> cellMap(mMapRow, std::vector<Cell>(mMapCol));
	std::priority_queue<Cell*, std::vector<Cell*>, Cell> openList;

	cellMap[srcR][srcC].f = cellMap[srcR][srcC].g = cellMap[srcR][srcC].h = 0;
	cellMap[srcR][srcC].r = srcR;
	cellMap[srcR][srcC].c = srcC;
	cellMap[srcR][srcC].parentR = srcR;
	cellMap[srcR][srcC].parentC = srcC;
	openList.push(&cellMap[srcR][srcC]);

	while (!openList.empty()) {
		Cell* curr = openList.top();
		int r = curr->r;
		int c = curr->c;
		openList.pop();

		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (IsValidCell(nr, nc) && !cellMap[nr][nc].isClosed) {
				if (nr == dstR && nc == dstC) {
					cellMap[nr][nc].parentR = r;
					cellMap[nr][nc].parentC = c;
					
					SavePath(cellMap, srcR, srcC, dstR, dstC);
					return true;
				}
				
				int ng = curr->g + 1;
				int nh = CalcHeuristic(nr, nc, dstR, dstC);
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

Vector2 MapManager::GetNextPath(const Vector2& worldPos)
{
	Vector2 pixelPos = WorldToPixel(worldPos);
	int r = static_cast<int>(pixelPos.y / mTileHeight);
	int c = static_cast<int>(pixelPos.x / mTileWidth);

	if (IsValidCell(r, c)) {
		int nr, nc, min = Math::INF, minDir = -1;

		for (int dir = 0; dir < 4; dir++) {
			nr = r + dr[dir];
			nc = c + dc[dir];

			if (IsValidCell(nr, nc) && mMap[nr][nc] < min) {
				min = mMap[nr][nc];
				minDir = dir;
			}
		}

		if (minDir != -1) {
			pixelPos.y += mTileHeight * dr[minDir];
			pixelPos.x += mTileWidth * dc[minDir];
			return PixelToWorld(pixelPos);
		}
	}

	return worldPos;
}

std::pair<int, int> MapManager::GetRowCol(const Vector2& worldPos)
{
	Vector2 pixelPos = WorldToPixel(worldPos);
	return std::pair<int, int>(pixelPos.y / mTileHeight - (pixelPos.y < 0), pixelPos.x / mTileWidth - (pixelPos.x < 0));
}

void MapManager::PrintMap()
{
	for (int r = 0; r < mMapRow; r++) {
		for (int c = 0; c < mMapCol; c++) {
			printf("%2d ", Math::Min(99, mMap[r][c]));
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
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

void MapManager::SetDaylight(Vector3 color)
{
	Renderer* renderer = GetGame()->GetRenderer();

	renderer->SetAmbientLight(color);
}

void MapManager::UpdateDaylight()
{
	float intensity = Math::Sin(Math::TWOPI * mTime / DAY_CYCLE) / 2 + 0.5f;
	SetDaylight(Vector3(intensity, intensity, intensity));

	if (mTime > DAY_CYCLE) mTime -= DAY_CYCLE;
}

int MapManager::CalcHeuristic(int r, int c, int fr, int fc)
{
	return static_cast<int>(Math::Abs(fr - r) + Math::Abs(fc - c));
}

bool MapManager::IsValidCell(int r, int c)
{
	return 0 <= r && r < mMapRow && 0 <= c && c < mMapCol && mMap[r][c] != -1;
}

void MapManager::SavePath(const std::vector<std::vector<Cell>>& cellMap, int sr, int sc, int fr, int fc)
{
	int r = fr, c = fc, pr, pc, len = 0;

	mMap[r][c] = len++;
	while (r != sr || c != sc) {
		pr = cellMap[r][c].parentR;
		pc = cellMap[r][c].parentC;
		r = pr;
		c = pc;

		mMap[r][c] = Math::Min(mMap[r][c], len);
		len++;
	}
}

bool MapManager::CheckWall(int r, int c) {
	for (int i = 0; i < 8; i++) {
		if (!IsValidCell(r + dr[i], c + dc[i])) return true;
	}

	return false;
}