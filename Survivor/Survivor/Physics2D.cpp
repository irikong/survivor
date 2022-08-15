#include "Physics2D.h"

Physics2D::Physics2D(Game* game) :
	mGame(game)
{

}

void Physics2D::AddCollider(ColliderComponent* collider)
{
	mColliders.emplace_back(collider);
}

void Physics2D::RemoveCollider(ColliderComponent* collider)
{
	auto iter = std::find(mColliders.begin(), mColliders.end(), collider);
	if (iter != mColliders.end()) {
		mColliders.erase(iter);
	}
}
