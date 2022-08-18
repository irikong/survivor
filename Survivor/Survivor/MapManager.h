#pragma once
#include "Actor.h"
class MapManager : public Actor
{
public:
	MapManager(class Game* game);
	~MapManager() = default;

private:
	void MakeWall(float fWidth, float fHeight, float mapRow, float mapCol);
};

