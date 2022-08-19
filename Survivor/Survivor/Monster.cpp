#include "Monster.h"
#include "Collision.h"
#include "BoxComponent.h"
#include "StateComponent.h"
#include "MonsterState.h"
#include "MoveComponent.h"
#include "AnimComponent.h"
#include "Player.h"
#include "Renderer.h"
#include "Texture.h"
#include "Game.h"
#include "Math.h"

Monster::Monster(Game* game) : 
	Actor(game),
	mHP(100)
{
	mAC = new AnimComponent(this, 32, 32);
	mAC->SetTexture(game->GetRenderer()->GetTexture("Monster.png"));
	mAC->SetAnimFPS(3.0f);
	mAC->AddAnim("Down", 0, 2);
	mAC->AddAnim("Left", 3, 5);
	mAC->AddAnim("Right", 6, 8);
	mAC->AddAnim("Up", 9, 11);
	mAC->SetCurrAnim("Down");

	mMC = new MoveComponent(this);
	mMC->SetSpeed(100.0f);

	AABB box(Vector2(-16, -16), Vector2(16, 16));
	mBC = new BoxComponent(this, box);

	mSC = new StateComponent(this);
	mSC->AddState(new MonsterPatrol(mSC));
	mSC->AddState(new MonsterFollow(mSC, this));
	mSC->AddState(new MonsterDeath(mSC, this));
	mSC->ChangeState("Follow");
}

void Monster::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
}

void Monster::MoveTo(Vector2 dir)
{
	if (Math::Abs(dir.x) > Math::Abs(dir.y)) {
		mAC->SetCurrAnim((dir.x > 0.0f ? "Right" : "Left"));
	}
	else {
		mAC->SetCurrAnim((dir.y > 0.0f ? "Up" : "Down"));
	}

	mMC->SetDirection(dir);
}

void Monster::Death()
{
	SetState(EDead);
}

void Monster::Hit(float damage)
{
	mHP -= damage;

	if (mHP <= 0.0f) {
		mSC->ChangeState("Death");
	}
}
