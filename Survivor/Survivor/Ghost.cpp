#include "Ghost.h"
#include "Game.h"
#include "AnimComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "MoveComponent.h"
#include "BoxComponent.h"
#include "StateComponent.h"
#include "MonsterState.h"

Ghost::Ghost(Game* game) :
	Monster(game, 100.0f, 50.0f)
{
	mMC->SetGroundCheck(false);

	mAC = new AnimComponent(this, 32, 32);
	mAC->SetTexture(game->GetRenderer()->GetTexture("Ghost.png"));
	mAC->SetAnimFPS(3.0f);
	mAC->AddAnim("Down", 0, 2);
	mAC->AddAnim("Left", 3, 5);
	mAC->AddAnim("Right", 6, 8);
	mAC->AddAnim("Up", 9, 11);
	mAC->SetCurrAnim("Down");

	AABB box(Vector2(-16, -16), Vector2(16, 16));
	mBC = new BoxComponent(this, box);

	mSC = new StateComponent(this);
	mSC->AddState(new MonsterFollow(mSC, this, false));
	mSC->AddState(new MonsterDeath(mSC, this));
	mSC->ChangeState("Follow");
}

void Ghost::UpdateActor(float deltaTime)
{
	Monster::UpdateActor(deltaTime);
}
