#include "InputComponent.h"
#include "Math.h"

InputComponent::InputComponent(Actor* owner) :
	MoveComponent(owner),
	mUpKey(),
	mDownKey(),
	mLeftKey(),
	mRightKey()
{

}

InputComponent::~InputComponent()
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	mDirection = Vector2::Zero;

	if (keyState[mUpKey]) {
		mDirection.y += 1.0f;
	}
	if (keyState[mDownKey]) {
		mDirection.y -= 1.0f;
	}

	if (keyState[mLeftKey]) {
		mDirection.x -= 1.0f;
	}
	if (keyState[mRightKey]) {
		mDirection.x += 1.0f;
	}
}
