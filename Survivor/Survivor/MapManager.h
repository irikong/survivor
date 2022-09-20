#pragma once
#include "Actor.h"
#include <vector>

class MapManager : public Actor
{
public:
	MapManager(class Game* game);
	~MapManager() = default;

	bool IsGround(const Vector2& pos);
	Vector2 WorldToPixel(const Vector2& worldPos);

private:
	void MakeWall(float fWidth, float fHeight, float mapRow, float mapCol);
	void MakeLight();

	float mMapWidth;
	float mMapHeight;
	Vector2 mPixelOffset; // world to pixel
	std::vector<std::vector<int>> mMap;
};

