#pragma once
class MonsterState
{
public:
	MonsterState(class StateComponent* sc);

	virtual void Update(float deltaTime) = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual const char* GetName() const = 0;

protected:
	class StateComponent* mSC;
};

class MonsterPatrol : public MonsterState {
public:
	MonsterPatrol(class StateComponent* sc);

	void Update(float deltaTime);
	void Enter();
	void Exit();
	const char* GetName() const override { return "Patrol"; }
};

class MonsterFollow : public MonsterState {
public:
	MonsterFollow(class StateComponent* sc, class Monster* monster);

	void Update(float deltaTime);
	void Enter();
	void Exit();
	const char* GetName() const override { return "Follow"; }

private:
	class Player* mTarget;
	class Monster* mMonster;
};

class MonsterDeath : public MonsterState {
public:
	MonsterDeath(class StateComponent* sc);

	void Update(float deltaTime);
	void Enter();
	void Exit();
	const char* GetName() const override { return "Death"; }
};
