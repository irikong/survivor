#pragma once
#include "ColliderComponent.h"
#include "Collision.h"

class BoxComponent : public ColliderComponent
{
public:
	BoxComponent(class Actor* owner, const AABB& box, int updateOrder = 50);
	~BoxComponent();

	void OnUpdateWorldTransform() override;

	Type GetType() const override { return kBoxComponent; }
	void SetBox(AABB& box) { mBox = box; }
	void SetMin(class Vector2& min) { mBox.mMin = min; }
	void SetMax(class Vector2& max) { mBox.mMax = max; }
	const AABB& GetWorldBox() const { return mBox; }

private:
	AABB mBox;
	AABB mWorldBox;
};

