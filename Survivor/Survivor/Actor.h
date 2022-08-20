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

	enum Layer {
		ENone,
		EPlayer,
		EMonster,
		EProp
	};

	Actor(class Game* game);
	virtual ~Actor();

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	void ComputeWorldTransform();
	virtual void OnCollision(class ColliderComponent* other);

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	Layer GetLayer() const { return mLayer; }
	void SetLayer(Layer layer) { mLayer = layer; }

	class Game* GetGame() const { return mGame; }
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }
	Vector2 GetRight() const { return Vector2(Math::Cos(mRotation - Math::PIDIV2), Math::Sin(mRotation - Math::PIDIV2)); }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	const Vector2& GetPosition() const { return mPosition; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetRotation(float rot) { mRotation = rot; mRecomputeWorldTransform = true; }
	void SetPosition(const Vector2& pos) { mPosition = pos; mRecomputeWorldTransform = true; }

private:
	State mState;
	Layer mLayer;

	class Game* mGame;
	std::vector<class Component*> mComponents;

	Vector2 mPosition;
	float mScale;
	float mRotation;
	
	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;
};