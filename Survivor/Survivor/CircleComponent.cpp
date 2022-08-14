#include "CircleComponent.h"
#include "Actor.h"
#include "Game.h"

CircleComponent::CircleComponent(Actor* owner, float radius, int updateOrder) : 
	ColliderComponent(owner, updateOrder),
	mCircle(Vector2::Zero, radius),
	mWorldCircle(owner->GetPosition(), radius)
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
