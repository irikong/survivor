#include "FiniteState.h"
#include "StateComponent.h"
#include "Monster.h"
#include "Player.h"
#include "Game.h"
#include "MapManager.h"
#include "MoveComponent.h"
#include "Random.h"
#include "Weapon.h"

FiniteState::FiniteState(StateComponent* sc) : 
	mSC(sc)
{
}

// MonsterPatrol
MonsterPatrol::MonsterPatrol(StateComponent* sc, Monster* monster, float aggroRange) :
	FiniteState(sc),
	mMonster(monster),
	PATROL_TIME(1.0f),
	REST_STACK(3),
	mPatrolTime(0.0f),
	mRestStack(0)
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
	else {
		mPatrolTime += deltaTime;
		if (mPatrolTime > PATROL_TIME) {
			mPatrolTime -= PATROL_TIME;

			if(!mRestStack) {
				int rand = Random::GetIntRange(0, 4);
				mMonster->MoveDir(Vector2(static_cast<float>(dx[rand]), static_cast<float>(dy[rand])));
				mRestStack = REST_STACK;
			}
			else {
				mRestStack--;
				mMonster->MoveDir(Vector2::Zero);
			}
		}
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
	FiniteState(sc),
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
	FiniteState(sc),
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

// WeaponReady
WeaponReady::WeaponReady(StateComponent* sc, Weapon* weapon) :
	FiniteState(sc),
	mWeapon(weapon)
{
}

void WeaponReady::Update(float deltaTime)
{
}

void WeaponReady::Enter()
{
	mWeapon->Ready();
}

void WeaponReady::Exit()
{
	
}

// WeaponFly
WeaponFly::WeaponFly(StateComponent* sc, Weapon* weapon) :
	FiniteState(sc),
	mWeapon(weapon),
	mFlyTime(1.0f)
{
	mMC = mWeapon->GetMoveComponent();
}

void WeaponFly::Update(float deltaTime)
{
	mFlyTime -= deltaTime;

	if (mFlyTime < 0)
		mSC->ChangeState("Stay");
	else
		mMC->SetSpeed(300.0f * Math::Sin(mFlyTime * Math::PIDIV2));
}

void WeaponFly::Enter()
{
	mWeapon->SetPosition(mWeapon->GetOwner()->GetPosition());
	mMC->SetDirection(mWeapon->GetOwner()->GetFace());
	mMC->SetSpeed(400.0f);
	mMC->SetAngularSpeed(Math::TWOPI);
	
	mFlyTime = 1.0f;
}

void WeaponFly::Exit()
{
	mMC->SetSpeed(0.0f);
}

// WeaponStay
WeaponStay::WeaponStay(StateComponent* sc, Weapon* weapon) : 
	FiniteState(sc),
	mWeapon(weapon),
	mStayTime(0.5f)
{
	mPlayer = mWeapon->GetOwner();
}

void WeaponStay::Update(float deltaTime)
{
	mStayTime -= deltaTime;

	if (mStayTime < 0)
		mSC->ChangeState("ComeBack");
}

void WeaponStay::Enter()
{
	mInitPos = mPlayer->GetPosition();
	mStayTime = 0.5f;
}

void WeaponStay::Exit()
{
	Vector2 lastPos = mPlayer->GetPosition();
	mWeapon->SetEstimatedPos(lastPos + (lastPos - mInitPos));
}

// WeaponComeBack
WeaponComeBack::WeaponComeBack(StateComponent* sc, Weapon* weapon) :
	FiniteState(sc),
	mWeapon(weapon),
	mComeBackTime(1.0f)
{
	mMC = mWeapon->GetMoveComponent();
}

void WeaponComeBack::Update(float deltaTime)
{
	mComeBackTime -= deltaTime;

	if (mComeBackTime < 0)
		mSC->ChangeState("Missing");
	else
		mMC->SetSpeed(-500.0f * Math::Sin((1 - mComeBackTime) * Math::PIDIV2));
}

void WeaponComeBack::Enter()
{
	mMC->SetDirection(mWeapon->GetPosition() - mWeapon->GetEstimatedPos());
	mMC->SetSpeed(0.0f);
	mMC->SetAngularSpeed(Math::TWOPI);

	mComeBackTime = 1.0f;
}

void WeaponComeBack::Exit()
{
}

// WeaponMissing
WeaponMissing::WeaponMissing(StateComponent* sc, Weapon* weapon) :
	FiniteState(sc),
	mWeapon(weapon),
	mReloadTime(2.0f)
{
}

void WeaponMissing::Update(float deltaTime)
{
	mReloadTime -= deltaTime;
	
	if (mReloadTime < 0)
		mSC->ChangeState("Ready");
}

void WeaponMissing::Enter()
{
	mReloadTime = 2.0f;
}

void WeaponMissing::Exit()
{
}
