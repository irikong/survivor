#pragma once
#include "Actor.h"

class Weapon : public Actor
{
public:
	Weapon(class Game* game, class Player* player);
	~Weapon() = default;

	void UpdateActor(float deltaTime) override;

	void OnCollision(class ColliderComponent* other) override;

private:
	class SpriteComponent* mSC;
	class CircleComponent* mCC;
	class MoveComponent* mMC;

	float mDamage;
	float mLifeTime;
};

