#pragma once
#include "Actor.h"
#include "Math.h"
#include <vector>

struct Cell {
	int f, g, h;
	int r, c;
	int parentR, parentC;
	bool isClosed;

	Cell() :
		f(Math::INF),
		g(Math::INF),
		h(Math::INF),
		r(-1),
		c(-1),
		parentR(-1),
		parentC(-1),
		isClosed(false)
	{}

	bool operator()(const Cell* lhs, const Cell* rhs) const {
		return lhs->f > rhs->f;
	}
};

class MapManager : public Actor
{
public:
	MapManager(class Game* game);
	~MapManager() = default;

	bool IsGround(const Vector2& pos);
	Vector2 WorldToPixel(const Vector2& worldPos);
	bool PathFinding(int sr, int sc, int fr, int fc);

private:
	void MakeWall(float fWidth, float fHeight, float mapRow, float mapCol);
	void MakeLight();
	int CalcHeuristic(int r, int c, int fr, int fc);

	int mMapRow;
	int mMapCol;
	float mMapWidth;
	float mMapHeight;
	Vector2 mPixelOffset; // world to pixel
	std::vector<std::vector<int>> mMap;
};

