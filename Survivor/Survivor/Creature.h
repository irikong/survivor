#pragma once
#include "Actor.h"
class Creature : public Actor
{
public:
	Creature(class Game* game, float hp, float speed);
	~Creature() = default;

	void UpdateActor(float deltaTime) override;

	virtual void Attack();
	virtual void Hit(float damage);
	virtual void Death();

protected:
	float mHP;
	float mSpeed;
};

