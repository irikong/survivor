#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	~MoveComponent();

	void Update(float deltaTime) override;

	Type GetType() const override { return kMoveComponent; }
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetVerticalSpeed() const { return mVerticalSpeed; }
	float GetHorizontalSpeed() const { return mHorizontalSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetVerticalSpeed(float speed) { mVerticalSpeed = speed; }
	void SetHorizontalSpeed(float speed) { mHorizontalSpeed = speed; }

private:
	float mAngularSpeed;
	float mVerticalSpeed;
	float mHorizontalSpeed;
};

