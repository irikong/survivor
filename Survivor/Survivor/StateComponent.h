#pragma once
#include "Component.h"
#include "FiniteState.h"
#include <unordered_map>

class StateComponent : public Component
{
public:
	StateComponent(class Actor* owner, int updateOrder = 100);
	~StateComponent() = default;

	void Update(float deltaTime) override;
	void ChangeState(const std::string& name);
	void AddState(FiniteState* state);

	Type GetType() const override { return kStateComponent; }
	FiniteState* GetCurrState() const { return mCurrState; }

private:
	std::unordered_map<std::string, FiniteState*> mStates;
	FiniteState* mCurrState;
};

