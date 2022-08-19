#pragma once
#include "Actor.h"

class Monster : public Actor
{
public:
	Monster(class Game* game, float hp, float speed);
	~Monster() = default;

	void UpdateActor(float deltaTime) override;

	void MoveTo(class Vector2 dir);
	void Death();
	void Hit(float damage);

protected:
	float mHP;
	float mSpeed;
	class AnimComponent* mAC;
	class MoveComponent* mMC;
	class BoxComponent* mBC;
	class StateComponent* mSC;
};

