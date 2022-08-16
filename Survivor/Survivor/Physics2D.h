#pragma once
#include "Collision.h"
#include <vector>

class Physics2D
{
public:
	Physics2D(class Game* game);
	
	void AddCircle(class CircleComponent* circle);
	void RemoveCircle(class CircleComponent* circle);
	void AddBox(class BoxComponent* box);
	void RemoveBox(class BoxComponent* box);

	void CollisionDetection(class CircleComponent* circle);
	void CollisionDetection(class BoxComponent* box);

private:
	class Game* mGame;
	std::vector<class CircleComponent*> mCircles;
	std::vector<class BoxComponent*> mBoxes;
};

