#pragma once
#include <vector>

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

	State GetState() { return mState; }
	class Game* GetGame() { return mGame; }

private:
	State mState;

	std::pair<int, int> mPosition;
	float mScale;
	float mRotation;

	class Game* mGame;
	std::vector<class Component*> mComponents;
};