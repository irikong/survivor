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
	Actor(game)
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
	mSC->AddState(new MonsterDeath(mSC));
	mSC->ChangeState("Follow");
}

void Monster::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
}

void Monster::MoveTo(Vector2 dir)
{
	mMC->SetDirection(dir);
}
