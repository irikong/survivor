#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	~MoveComponent();

	void Update(float deltaTime) override;

	Type GetType() const override { return kMoveComponent; }
	float GetAngularSpeed() const { return mAngularSpeed; }
	Vector2 GetDirection() const { return mDirection; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetDirection(Vector2 dir) { mDirection = dir; }
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetGroundCheck(bool check) { mGroundCheck = check; }

protected:
	Vector2 mDirection;
	float mSpeed;
	bool mGroundCheck;

private:
	float mAngularSpeed;
};

