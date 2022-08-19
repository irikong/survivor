#include "StateComponent.h"
#include "MonsterState.h"

StateComponent::StateComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder),
	mCurrState(nullptr)
{

}

void StateComponent::Update(float deltaTime)
{
	if (mCurrState)
		mCurrState->Update(deltaTime);
}

void StateComponent::ChangeState(const std::string& name)
{
	if (mCurrState)
		mCurrState->Exit();

	auto iter = mStates.find(name);
	if (iter != mStates.end()) {
		mCurrState = iter->second;
		mCurrState->Enter();
	}
}

void StateComponent::AddState(MonsterState* state)
{
	mStates.emplace(state->GetName(), state);
}
