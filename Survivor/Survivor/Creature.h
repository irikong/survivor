#pragma once
#include "Actor.h"
class Creature : public Actor
{
public:
	Creature(class Game* game, int hp, float speed);
	~Creature() = default;

	void UpdateActor(float deltaTime) override;

	virtual void Attack();
	virtual void Hit(int damage);
	virtual void Death();

protected:
	int mHP;
	float mSpeed;
};

