#include "InputComponent.h"

InputComponent::InputComponent(Actor* owner) :
	MoveComponent(owner)
{

}

InputComponent::~InputComponent()
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	float verticalSpeed = 0.0f;
	if (keyState[mUpKey]) {
		verticalSpeed += mMaxVerticalSpeed;
	}
	if (keyState[mDownKey]) {
		verticalSpeed -= mMaxVerticalSpeed;
	}
	SetVerticalSpeed(verticalSpeed);

	float horizontalSpeed = 0.0f;
	if (keyState[mLeftKey]) {
		horizontalSpeed -= mMaxHorizontalSpeed;
	}
	if (keyState[mRightKey]) {
		horizontalSpeed += mMaxHorizontalSpeed;
	}
	SetHorizontalSpeed(horizontalSpeed);
}
