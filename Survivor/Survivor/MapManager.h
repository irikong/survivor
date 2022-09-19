#pragma once
#include "Actor.h"
#include <vector>

class MapManager : public Actor
{
public:
	MapManager(class Game* game);
	~MapManager() = default;

private:
	void MakeWall(float fWidth, float fHeight, float mapRow, float mapCol);
	void MakeLight();

	std::vector<std::vector<int>> mMap;
};

