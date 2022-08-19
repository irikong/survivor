#pragma once
#include "Component.h"
#include <unordered_map>

class StateComponent : public Component
{
public:
	StateComponent(class Actor* owner, int updateOrder = 100);
	~StateComponent() = default;

	void Update(float deltaTime) override;
	void ChangeState(const std::string& name);
	void AddState(class MonsterState* state);

	Type GetType() const override { return kStateComponent; }

private:
	std::unordered_map<std::string, class MonsterState*> mStates;
	class MonsterState* mCurrState;
};

