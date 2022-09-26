#include "MonsterState.h"
#include "StateComponent.h"
#include "Monster.h"
#include "Player.h"
#include "Game.h"
#include "Math.h"
#include "MapManager.h"

MonsterState::MonsterState(StateComponent* sc) : 
	mSC(sc)
{
}

// MonsterPatrol
MonsterPatrol::MonsterPatrol(StateComponent* sc, Monster* monster, float aggroRange) :
	MonsterState(sc),
	mMonster(monster)
{
	mTarget = monster->GetGame()->GetPlayer();
	mAggroRangeSq = aggroRange * aggroRange;
}

void MonsterPatrol::Update(float deltaTime)
{
	Vector2 dir = mTarget->GetPosition() - mMonster->GetPosition();
	if (dir.LengthSq() < mAggroRangeSq) {
		mSC->ChangeState("Follow");
	}
}

void MonsterPatrol::Enter()
{
}

void MonsterPatrol::Exit()
{
}

// MonsterFollow
MonsterFollow::MonsterFollow(StateComponent* sc, Monster* monster, bool useNav) :
	MonsterState(sc),
	mMonster(monster),
	mUseNav(useNav)
{
	Game* game = monster->GetGame();
	mTarget = game->GetPlayer();
	mMM = game->GetMapManager();
}

void MonsterFollow::Update(float deltaTime)
{
	if (mTarget) {
		Vector2 dir = mTarget->GetPosition() - mMonster->GetPosition();

		if (mUseNav && dir.Length() > 32) {
			dir = mMM->GetNextPath(mMonster->GetPosition()) - mMonster->GetPosition();
		}
		
		mMonster->MoveDir(dir);
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
