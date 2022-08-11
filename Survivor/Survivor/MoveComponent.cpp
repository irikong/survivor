#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder),
	mAngularSpeed(0.0f),
	mDirection(),
	mSpeed(0.0f)
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

	if (!Math::NearZero(mDirection.Length())) {
		mDirection.Normalize();
		Vector2 velocity = mDirection * mSpeed;
		mOwner->SetPosition(mOwner->GetPosition() + velocity * deltaTime);
	}
}
