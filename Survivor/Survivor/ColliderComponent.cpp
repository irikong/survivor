#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder),
	isTrigger(false)
{

}
