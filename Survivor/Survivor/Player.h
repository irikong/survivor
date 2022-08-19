#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player(class Game* game);
	~Player() = default;

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	void OnCollision(class ColliderComponent* other) override;
	void ResolveCollision(const struct AABB& other);

	void Hit(float damage);

private:
	class InputComponent* mIC;
	class AnimComponent* mAC;
	class BoxComponent* mBC;

	float mHP;

	bool mIsInvincible;
	float mITime;
	float mCurrITime;
};

