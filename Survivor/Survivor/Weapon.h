#pragma once
#include "Actor.h"

class Weapon : public Actor
{
public:
	Weapon(class Game* game, class Player* player);
	~Weapon() = default;

	void UpdateActor(float deltaTime) override;

	void OnCollision(class ColliderComponent* other) override;
	void Ready();
	void Use();

	class MoveComponent* GetMoveComponent() const { return mMC; }
	Vector2 GetEstimatedPos() const { return mEstimatedPos; }
	void SetEstimatedPos(Vector2 pos) { mEstimatedPos = pos; }
	Player* GetOwner() const { return mOwner; }

private:
	class Player* mOwner;

	class SpriteComponent* mSC;
	class CircleComponent* mCC;
	class MoveComponent* mMC;
	class StateComponent* mFSM;

	Vector2 mEstimatedPos;
	int mDamage;
	float mLifeTime;

	bool mIsReady;
};

