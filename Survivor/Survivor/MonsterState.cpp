#include "MonsterState.h"
#include "StateComponent.h"
#include "Monster.h"
#include "Player.h"
#include "Game.h"
#include "Math.h"

MonsterState::MonsterState(StateComponent* sc) : 
	mSC(sc)
{
}

// MonsterPatrol
MonsterPatrol::MonsterPatrol(StateComponent* sc) :
	MonsterState(sc)
{
}

void MonsterPatrol::Update(float deltaTime)
{
}

void MonsterPatrol::Enter()
{
}

void MonsterPatrol::Exit()
{
}

// MonsterFollow
MonsterFollow::MonsterFollow(StateComponent* sc, Monster* monster) :
	MonsterState(sc),
	mMonster(monster)
{
	mTarget = monster->GetGame()->GetPlayer();
}

void MonsterFollow::Update(float deltaTime)
{
	if (mTarget) {
		Vector2 dir = mTarget->GetPosition() - mMonster->GetPosition();
		mMonster->MoveTo(dir);
	}
}

void MonsterFollow::Enter()
{
}

void MonsterFollow::Exit()
{
}

// MonsterDeath
MonsterDeath::MonsterDeath(StateComponent* sc, Monster* monster) :
	MonsterState(sc),
	mMonster(monster)
{
}

void MonsterDeath::Update(float deltaTime)
{
}

void MonsterDeath::Enter()
{
	mMonster->Death();
}

void MonsterDeath::Exit()
{
}
