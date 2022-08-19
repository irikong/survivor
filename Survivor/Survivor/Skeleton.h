#pragma once
#include "Monster.h"

class Skeleton : public Monster
{
public:
	Skeleton(class Game* game);
	~Skeleton() = default;

	void UpdateActor(float deltaTime) override;

private:

};

