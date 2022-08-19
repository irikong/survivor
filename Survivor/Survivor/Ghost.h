#pragma once
#include "Monster.h"
class Ghost : public Monster
{
public:
	Ghost(class Game* game);
	~Ghost() = default;

	void UpdateActor(float deltaTime) override;

private:
};

