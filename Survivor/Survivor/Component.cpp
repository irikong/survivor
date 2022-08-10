#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder) :
	mOwner(owner),
	mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::ProcessInput(const uint8_t* keyState)
{
}

void Component::Update(float deltaTime)
{
}

void Component::OnUpdateWorldTransform()
{
}
