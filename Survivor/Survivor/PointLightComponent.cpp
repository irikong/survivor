#include "PointLightComponent.h"
#include "Renderer.h"
#include "Actor.h"
#include "Game.h"
#include "Random.h"

PointLightComponent::PointLightComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder),
	mColorOrigin(Vector3(1, 1, 1)),
	mRangeOrigin(50),
	mFollowState(true),
	mFlickState(false),
	mDT(0.0f)
{
	mPointLight = new PointLight{ Vector3::Zero, mColorOrigin, mRangeOrigin };
	owner->GetGame()->GetRenderer()->AddPointLight(mPointLight);
}

PointLightComponent::~PointLightComponent()
{
	mOwner->GetGame()->GetRenderer()->RemovePointLight(mPointLight);
	delete mPointLight;
}

void PointLightComponent::Update(float deltaTime)
{
	mDT += deltaTime;

	if (mFlickState && mDT > 0.05f) {
		Flick();
		mDT = 0;
	}
}

void PointLightComponent::OnUpdateWorldTransform()
{
	if(mFollowState)
		FollowOwner();
}


void PointLightComponent::SetActive(bool active)
{
	if (active) mPointLight->mColor = mColorOrigin;
	else mPointLight->mColor = Vector3::Zero;
}

void PointLightComponent::FollowOwner()
{
	SetLightPosition(mOwner->GetPosition());
}

void PointLightComponent::Flick()
{
	float f = Random::GetFloatRange(0.01, 0.05);
	mPointLight->mColor = Vector3(mColorOrigin.x + f, mColorOrigin.y + f, mColorOrigin.z + f);

	mPointLight->mFallOffRange = mRangeOrigin * (1 + f);
}
