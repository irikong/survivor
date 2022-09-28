#pragma once
#include "Creature.h"

class Player : public Creature
{
public:
	Player(class Game* game, float hp, float speed);
	~Player() = default;

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	void OnCollision(class ColliderComponent* other) override;
	void ResolveCollision(const struct AABB& other);

	void Attack() override;
	void Hit(float damage) override;
	void Death() override;

	Vector2 GetFace() { return mFace; }

private:
	class InputComponent* mIC;
	class AnimComponent* mAC;
	class BoxComponent* mBC;

	std::pair<int, int> mCurrRowCol;

	bool mIsInvincible;
	const float mITime;
	float mCurrITime;

	Vector2 mFace;

	class Weapon* mWeapon;
};

