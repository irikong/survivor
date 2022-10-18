#pragma once
#include "Creature.h"

class Monster : public Creature
{
public:
	Monster(class Game* game, int hp, float speed);
	~Monster();

	void UpdateActor(float deltaTime) override;

	void Attack() override;
	void Hit(int damage) override;
	void Death() override;
	void MoveDir(class Vector2 dir);

protected:
	class AnimComponent* mAC;
	class MoveComponent* mMC;
	class BoxComponent* mBC;
	class StateComponent* mSC;
};

