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

	void FollowOwner();
	void SetActive(bool active);

	Type GetType() const override { return kPointLightComponent; }
	Vector2 GetLightPosition() { return Vector2(mPointLight->mPosition.x, mPointLight->mPosition.y); }
	Vector3 GetLightColor() { return mColor; }
	void SetLightPosition(Vector2 pos) { mPointLight->mPosition = Vector3(pos.x, pos.y, 0); }
	void SetLightColor(Vector3 color) { mColor = color; mPointLight->mColor = mColor; }
	void SetLightFallOffRange(float range) { mPointLight->mFallOffRange = range; }

private:
	PointLight* mPointLight;
	Vector3 mColor;
	bool mFollowState;
};

