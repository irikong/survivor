#include "BoxComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Physics2D.h"

BoxComponent::BoxComponent(Actor* owner, const AABB& box, int updateOrder) : 
	ColliderComponent(owner, updateOrder),
	mBox(box),
	mWorldBox()
{
	owner->GetGame()->GetPhysics2D()->AddBox(this);
	OnUpdateWorldTransform();
}

BoxComponent::~BoxComponent()
{
	mOwner->GetGame()->GetPhysics2D()->RemoveBox(this);
}

void BoxComponent::OnUpdateWorldTransform()
{
	mWorldBox.mMin = mBox.mMin * mOwner->GetScale() + mOwner->GetPosition();
	mWorldBox.mMax = mBox.mMax * mOwner->GetScale() + mOwner->GetPosition();
}
