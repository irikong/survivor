#include "BoxComponent.h"
#include "Actor.h"

BoxComponent::BoxComponent(Actor* owner, const AABB& box, int updateOrder) : 
	ColliderComponent(owner, updateOrder),
	mBox(box),
	mWorldBox()
{
	// AddCollider()
}

BoxComponent::~BoxComponent()
{
	// RemoveCollider()
}

void BoxComponent::OnUpdateWorldTransform()
{
	mWorldBox.mMin = mBox.mMin * mOwner->GetScale() + mOwner->GetPosition();
	mWorldBox.mMax = mBox.mMax * mOwner->GetScale() + mOwner->GetPosition();
}
