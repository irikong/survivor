#pragma once
#include "ColliderComponent.h"
#include "Collision.h"

class CircleComponent : public ColliderComponent
{
public:
	CircleComponent(class Actor* owner, const Circle& circle, int updateOrder = 50);
	~CircleComponent();

	void OnUpdateWorldTransform() override;

	Type GetType() const override { return kCircleComponent; }
	void SetRadius(float radius) { mCircle.mRadius = radius; }
	float GetRadius() const { return mCircle.mRadius; }
	const Circle& GetWorldCircle() const { return mWorldCircle; }

private:
	Circle mCircle;
	Circle mWorldCircle;
};

