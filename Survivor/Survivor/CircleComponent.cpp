#include "CircleComponent.h"
#include "Actor.h"
#include "Game.h"

CircleComponent::CircleComponent(Actor* owner, const Circle& circle, int updateOrder) :
	ColliderComponent(owner, updateOrder),
	mCircle(circle),
	mWorldCircle()
{
	owner->GetGame()->AddCircle(this);
}

CircleComponent::~CircleComponent()
{
	mOwner->GetGame()->RemoveCircle(this);
}

void CircleComponent::OnUpdateWorldTransform()
{
	mWorldCircle.mCenter = mCircle.mCenter + mOwner->GetPosition();
	mWorldCircle.mRadius = mCircle.mRadius * mOwner->GetScale();
}
