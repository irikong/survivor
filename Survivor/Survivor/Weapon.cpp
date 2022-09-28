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
#include "FiniteState.h"
#include "StateComponent.h"

Weapon::Weapon(Game* game, Player* player) :
	Actor(game),
	mDamage(50.0f),
	mLifeTime(2.0f)
{
	SetPosition(player->GetPosition());

	mSC = new SpriteComponent(this);
	mSC->SetTexture(game->GetRenderer()->GetTexture("Boomerang.png"));

	mCC = new CircleComponent(this, Circle(Vector2::Zero, 16.f));
	
	mMC = new MoveComponent(this);
	mMC->SetGroundCheck(false);

	mFSM = new StateComponent(this);
	mFSM->AddState(new WeaponReady(mFSM, this));
	mFSM->AddState(new WeaponFly(mFSM, this));
	mFSM->AddState(new WeaponStay(mFSM, this));
	mFSM->AddState(new WeaponComeBack(mFSM, this));
	mFSM->ChangeState("Fly");
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
}
