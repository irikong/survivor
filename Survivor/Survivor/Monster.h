#pragma once
#include "Creature.h"

class Monster : public Creature
{
public:
	Monster(class Game* game, float hp, float speed);
	~Monster() = default;

	void UpdateActor(float deltaTime) override;

	void Attack() override;
	void Hit(float damage) override;
	void Death() override;
	void MoveTo(class Vector2 dir);

protected:
	class AnimComponent* mAC;
	class MoveComponent* mMC;
	class BoxComponent* mBC;
	class StateComponent* mSC;
};

