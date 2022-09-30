#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Math.h"

class PointLightComponent : public Component
{
public:
	PointLightComponent(Actor* owner, int updateOrder = 100);
	~PointLightComponent() override;

	void Update(float deltaTime) override;
	void OnUpdateWorldTransform() override;

	void SetActive(bool active);

	Type GetType() const override { return kPointLightComponent; }
	Vector2 GetLightPosition() { return Vector2(mPointLight->mPosition.x, mPointLight->mPosition.y); }
	Vector3 GetLightColor() { return mColorOrigin; }
	void SetLightPosition(Vector2 pos) { mPointLight->mPosition = Vector3(pos.x, pos.y, 0); }
	void SetLightColor(Vector3 color) { mColorOrigin = color; mPointLight->mColor = mColorOrigin; }
	void SetLightRange(float range) { mRangeOrigin = range; mPointLight->mRange = mRangeOrigin; }
	void SetLightFallOffRange(float range) { mFallOffRangeOrigin = range;  mPointLight->mFallOffRange = mFallOffRangeOrigin; }
	void SetFlickState(bool state) { mFlickState = state; }

private:
	void FollowOwner();
	void Flick();

	PointLight* mPointLight;
	Vector3 mColorOrigin;
	float mRangeOrigin;
	float mFallOffRangeOrigin;

	bool mFollowState;
	bool mFlickState;
	float mDT;
};

