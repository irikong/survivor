#pragma once
#include "Math.h"

class FiniteState
{
public:
	FiniteState(class StateComponent* sc);

	virtual void Update(float deltaTime) = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual const char* GetName() const = 0;

protected:
	class StateComponent* mSC;
};

class MonsterPatrol : public FiniteState {
public:
	MonsterPatrol(class StateComponent* sc, class Monster* monster, float aggroRange);

	void Update(float deltaTime);
	void Enter();
	void Exit();
	const char* GetName() const override { return "Patrol"; }

private:
	const int dx[5] = { 0, 0, 1, 0, -1 };
	const int dy[5] = { 0, 1, 0, -1, 0 };
	const float PATROL_TIME;
	const int REST_STACK;

	class Player* mTarget;
	class Monster* mMonster;
	float mAggroRangeSq;
	float mPatrolTime;
	int mRestStack;
};

class MonsterFollow : public FiniteState {
public:
	MonsterFollow(class StateComponent* sc, class Monster* monster, bool useNav);

	void Update(float deltaTime);
	void Enter();
	void Exit();
	const char* GetName() const override { return "Follow"; }

private:
	class Player* mTarget;
	class Monster* mMonster;
	class MapManager* mMM;
	bool mUseNav;
};

class MonsterDeath : public FiniteState {
public:
	MonsterDeath(class StateComponent* sc, class Monster* monster);

	void Update(float deltaTime);
	void Enter();
	void Exit();
	const char* GetName() const override { return "Death"; }

private:
	class Monster* mMonster;
};

class WeaponReady : public FiniteState {
public:
	WeaponReady(class StateComponent* sc, class Weapon* weapon);

	void Update(float deltaTime);
	void Enter();
	void Exit();
	const char* GetName() const override { return "Ready"; }

private:
	class Weapon* mWeapon;
};

class WeaponFly : public FiniteState {
public:
	WeaponFly(class StateComponent* sc, class Weapon* weapon);

	void Update(float deltaTime);
	void Enter();
	void Exit();
	const char* GetName() const override { return "Fly"; }

private:
	class Weapon* mWeapon;
	class MoveComponent* mMC;
	float mFlyTime;
};

class WeaponStay : public FiniteState {
public:
	WeaponStay(class StateComponent* sc, class Weapon* weapon);

	void Update(float deltaTime);
	void Enter();
	void Exit();
	const char* GetName() const override { return "Stay"; }

private:
	class Weapon* mWeapon;
	class Player* mPlayer;
	Vector2 mInitPos;
	float mFlyTime;
};

class WeaponComeBack : public FiniteState {
public:
	WeaponComeBack(class StateComponent* sc, class Weapon* weapon);

	void Update(float deltaTime);
	void Enter();
	void Exit();
	const char* GetName() const override { return "ComeBack"; }

private:
	class Weapon* mWeapon;
	class MoveComponent* mMC;
	float mFlyTime;
};