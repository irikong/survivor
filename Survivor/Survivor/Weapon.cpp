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

Weapon::Weapon(Game* game, Player* player) :
	Actor(game),
	mDamage(50.0f),
	mLifeTime(2.0f)
{
	SetPosition(player->GetPosition());

	mSC = new SpriteComponent(this);
	mSC->SetTexture(game->GetRenderer()->GetTexture("Circle.png"));

	mCC = new CircleComponent(this, Circle(Vector2::Zero, 16.f));
	
	mMC = new MoveComponent(this);
	mMC->SetDirection(player->GetFace());
	mMC->SetSpeed(300.0f);
}

void Weapon::UpdateActor(float deltaTime)
{
	mLifeTime -= deltaTime;

	if (mLifeTime < 0.0f) {
		SetState(EDead);
	}
	else {
		GetGame()->GetPhysics2D()->CollisionDetection(mCC);
	}
}

void Weapon::OnCollision(ColliderComponent* other)
{
	if (other->GetOwner()->GetLayer() == EMonster) {
		static_cast<Monster*>(other->GetOwner())->Hit(mDamage);
		SetState(EDead);
	}
}
