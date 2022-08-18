#pragma once
#include "Actor.h"

class Monster : public Actor
{
public:
	Monster(class Game* game);
	~Monster() = default;

	void UpdateActor(float deltaTime) override;

	void MoveTo(class Vector2 dir);

private:
	class AnimComponent* mAC;
	class MoveComponent* mMC;
	class BoxComponent* mBC;
	class StateComponent* mSC;
};

