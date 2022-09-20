#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"
#include "Game.h"
#include "MapManager.h"

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

	if (mDirection != Vector2::Zero) {
		mDirection.Normalize();
		Vector2 velocity = mDirection * mSpeed;
		Vector2 nextPos = mOwner->GetPosition() + velocity * deltaTime;
		
		if(mOwner->GetGame()->GetMapManager()->IsWalkable(nextPos))
			mOwner->SetPosition(nextPos);
	}
}
