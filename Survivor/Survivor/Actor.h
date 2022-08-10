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

	State GetState() const { return mState; }
	class Game* GetGame() const { return mGame; }
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	const Vector2& GetPosition() const { return mPosition; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetRotation(float rot) { mRotation = rot; mRecomputeWorldTransform = true; }
	void SetPosition(const Vector2& pos) { mPosition = pos; mRecomputeWorldTransform = true; }

private:
	State mState;

	class Game* mGame;
	std::vector<class Component*> mComponents;

	Vector2 mPosition;
	float mScale;
	float mRotation;
	
	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;
};