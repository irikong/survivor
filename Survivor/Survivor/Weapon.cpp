#include "Weapon.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "Player.h"
#include "Physics2D.h"
#include "Monster.h"
#include "StateComponent.h"

Weapon::Weapon(Game* game, Player* player) :
	Actor(game),
	mDamage(5),
	mLifeTime(2.0f),
	mIsReady(true),
	mOwner(player)
{
	SetPosition(player->GetPosition());

	mSC = new SpriteComponent(this, 120);
	mSC->SetTexture(game->GetRenderer()->GetTexture("Boomerang.png"));

	mCC = new CircleComponent(this, Circle(Vector2::Zero, 16.f));
	
	mMC = new MoveComponent(this);
	mMC->SetGroundCheck(false);

	mFSM = new StateComponent(this);
	mFSM->AddState(new WeaponReady(mFSM, this));
	mFSM->AddState(new WeaponFly(mFSM, this, 250.0f));
	mFSM->AddState(new WeaponStay(mFSM, this));
	mFSM->AddState(new WeaponComeBack(mFSM, this, 500.0f));
	mFSM->AddState(new WeaponMissing(mFSM, this));
	mFSM->ChangeState("Ready");
}

void Weapon::UpdateActor(float deltaTime)
{
	GetGame()->GetPhysics2D()->CollisionDetection(mCC);
}

void Weapon::OnCollision(ColliderComponent* other)
{
	if (other->GetOwner()->GetLayer() == EMonster) {
		static_cast<Monster*>(other->GetOwner())->Hit(mDamage);
	}
	if (other->GetOwner()->GetLayer() == EPlayer) {
		const char* stateName = mFSM->GetCurrState()->GetName();
		
		if(stateName == "Stay" || stateName == "ComeBack")
			mFSM->ChangeState("Ready");
	}
}

void Weapon::Ready()
{
	mIsReady = true;
	mSC->SetAlpha(0.0f);
	SetState(EPaused);
}

void Weapon::Use()
{
	if (mIsReady) {
		mIsReady = false;
		mSC->SetAlpha(1.0f);
		SetState(EActive);
		mFSM->ChangeState("Fly");
	}
}
