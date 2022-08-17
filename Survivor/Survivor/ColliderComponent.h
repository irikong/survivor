#pragma once
#include "Component.h"

class ColliderComponent : public Component
{
public:
	ColliderComponent(class Actor* owner, int updateOrder = 50);
	~ColliderComponent() = default;

	Type GetType() const override { return kColliderComponent; }
	void SetTrigger(bool b) { isTrigger = b; }

private:
	bool isTrigger;
};

