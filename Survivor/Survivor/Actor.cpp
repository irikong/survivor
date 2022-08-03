#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game* game) :
	mState(EActive),
	mGame(game),
	mPosition{ 0.0f,0.0f },
	mScale(1.0f),
	mRotation(0.0f),
	mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	
	while (!mComponents.empty())
		delete mComponents.back();
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive) {
		ComputeWorldTransform();

		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
	int order = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	while (iter != mComponents.end()) {
		if (order < (*iter)->GetUpdateOrder()) break;

		iter++;
	}

	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform) {
		mRecomputeWorldTransform = false;

		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(mPosition.first, mPosition.second, 0.0f);

		for (auto comp : mComponents) {
			comp->OnUpdateWorldTransform();
		}
	}
}
