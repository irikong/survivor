#pragma once
#include <vector>
#include "Math.h"

class Actor
{
public:
	enum State {
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	void ComputeWorldTransform();

	State GetState() { return mState; }
	class Game* GetGame() { return mGame; }
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

private:
	State mState;

	class Game* mGame;
	std::vector<class Component*> mComponents;

	std::pair<float, float> mPosition;
	float mScale;
	float mRotation;
	
	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;
};