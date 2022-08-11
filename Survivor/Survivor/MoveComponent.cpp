#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder),
	mAngularSpeed(0.0f),
	mVerticalSpeed(0.0f),
	mHorizontalSpeed(0.0f)
{

}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed)) {
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}

	if (!Math::NearZero(mVerticalSpeed)) {
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mVerticalSpeed * deltaTime;
		mOwner->SetPosition(pos);
	}

	if (!Math::NearZero(mHorizontalSpeed)) {
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetRight() * mHorizontalSpeed * deltaTime;
		mOwner->SetPosition(pos);
	}
}
