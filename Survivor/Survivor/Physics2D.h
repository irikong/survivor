#pragma once
#include "Collision.h"
#include <vector>

class Physics2D
{
public:
	Physics2D(class Game* game);
	
	void AddCollider(class ColliderComponent* collider);
	void RemoveCollider(class ColliderComponent* collider);

	std::vector<class ColliderComponent*> GetColliders() { return mColliders; }

private:
	class Game* mGame;
	std::vector<class ColliderComponent*> mColliders;
};

