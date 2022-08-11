#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);
	~InputComponent();

	void ProcessInput(const uint8_t* keyState) override;

	void SetMaxVerticalSpeed(float speed) { mMaxVerticalSpeed = speed; }
	void SetMaxHorizontalSpeed(float speed) { mMaxHorizontalSpeed = speed; }
	void SetUpKey(int key) { mUpKey = key; }
	void SetDownKey(int key) { mDownKey = key; }
	void SetLeftKey(int key) { mLeftKey = key; }
	void SetRightKey(int key) { mRightKey = key; }

private:
	float mMaxVerticalSpeed;
	float mMaxHorizontalSpeed;

	int mUpKey;
	int mDownKey;
	int mLeftKey;
	int mRightKey;
};

