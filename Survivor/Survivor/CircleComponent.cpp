#include "CircleComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Physics2D.h"

CircleComponent::CircleComponent(Actor* owner, const Circle& circle, int updateOrder) :
	ColliderComponent(owner, updateOrder),
	mCircle(circle),
	mWorldCircle()
{
	owner->GetGame()->GetPhysics2D()->AddCollider(this);
}

CircleComponent::~CircleComponent()
{
	mOwner->GetGame()->GetPhysics2D()->RemoveCollider(this);
}

void CircleComponent::OnUpdateWorldTransform()
{
	mWorldCircle.mCenter = mCircle.mCenter + mOwner->GetPosition();
	mWorldCircle.mRadius = mCircle.mRadius * mOwner->GetScale();
}
