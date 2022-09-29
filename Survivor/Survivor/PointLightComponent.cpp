#include "PointLightComponent.h"
#include "Renderer.h"
#include "Actor.h"
#include "Game.h"

PointLightComponent::PointLightComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder),
	mFollowState(true)
{
	mPointLight = new PointLight{ Vector3(0, 0, 0), Vector3(1, 1, 1), 50 };
	owner->GetGame()->GetRenderer()->AddPointLight(mPointLight);
}

PointLightComponent::~PointLightComponent()
{
	mOwner->GetGame()->GetRenderer()->RemovePointLight(mPointLight);
	delete mPointLight;
}

void PointLightComponent::Update(float deltaTime)
{
}

void PointLightComponent::OnUpdateWorldTransform()
{
	if(mFollowState)
		FollowOwner();
}

void PointLightComponent::FollowOwner()
{
	SetLightPosition(mOwner->GetPosition());
}

void PointLightComponent::SetActive(bool active)
{
	if (active) mPointLight->mColor = mColor;
	else mPointLight->mColor = Vector3::Zero;
}
