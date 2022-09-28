#include "Monster.h"
#include "Collision.h"
#include "BoxComponent.h"
#include "StateComponent.h"
#include "FiniteState.h"
#include "MoveComponent.h"
#include "AnimComponent.h"
#include "Player.h"
#include "Renderer.h"
#include "Texture.h"
#include "Game.h"
#include "Math.h"

Monster::Monster(Game* game, float hp, float speed) : 
	Creature(game, hp, speed),
	mAC(),
	mMC(),
	mBC(),
	mSC()
{
	SetLayer(EMonster);

	mMC = new MoveComponent(this);
	mMC->SetSpeed(speed);

	game->AddMonster(this);
}

Monster::~Monster()
{
	GetGame()->RemoveMonster(this);
}

void Monster::UpdateActor(float deltaTime)
{
	Creature::UpdateActor(deltaTime);
}

void Monster::Attack()
{
}

void Monster::Hit(float damage)
{
	mHP -= damage;

	if (mHP <= 0.0f) {
		mSC->ChangeState("Death");
	}
}

void Monster::Death()
{
	SetState(EDead);
}

void Monster::MoveDir(Vector2 dir)
{
	if (Math::Abs(dir.x) > Math::Abs(dir.y)) {
		mAC->SetCurrAnim((dir.x > 0.0f ? "Right" : "Left"));
	}
	else {
		mAC->SetCurrAnim((dir.y > 0.0f ? "Up" : "Down"));
	}

	mMC->SetDirection(dir);
}
