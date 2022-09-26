#include "Player.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "AnimComponent.h"
#include "InputComponent.h"
#include "Collision.h"
#include "CircleComponent.h"
#include "BoxComponent.h"
#include "Physics2D.h"
#include "Math.h"
#include "Monster.h"
#include "Weapon.h"
#include "MapManager.h"

Player::Player(Game* game, float hp, float speed) :
	Creature(game, hp, speed),
	mIsInvincible(false),
	mITime(0.5f),
	mCurrITime(0.0f),
	mAttackCoolTime(1.0f),
	mCurrCoolTime(0.0f),
	mFace(Vector2::Down)
{
	SetLayer(EPlayer);

	mAC = new AnimComponent(this, 32, 32);
	mAC->SetTexture(game->GetRenderer()->GetTexture("Player.png"));
	mAC->SetAnimFPS(3.0f);
	mAC->AddAnim("Down", 0, 2);
	mAC->AddAnim("Left", 3, 5);
	mAC->AddAnim("Right", 6, 8);
	mAC->AddAnim("Up", 9, 11);
	mAC->SetCurrAnim("Down");

	mIC = new InputComponent(this);
	mIC->SetUpKey(SDL_SCANCODE_UP);
	mIC->SetDownKey(SDL_SCANCODE_DOWN);
	mIC->SetLeftKey(SDL_SCANCODE_LEFT);
	mIC->SetRightKey(SDL_SCANCODE_RIGHT);
	mIC->SetSpeed(speed);

	AABB box(Vector2(-16, -16), Vector2(16, 16));
	mBC = new BoxComponent(this, box);
}

void Player::UpdateActor(float deltaTime)
{
	Creature::UpdateActor(deltaTime);

	if (mIsInvincible) {
		mCurrITime += deltaTime;
		float alpha = (Math::Cos(4.0f * Math::TWOPI * (mCurrITime / mITime)) + 3.0f) / 4.0f;
		mAC->SetAlpha(alpha);

		if (mCurrITime > mITime) {
			mAC->SetAlpha(1.0f);
			mIsInvincible = false;
		}
	}

	GetGame()->GetPhysics2D()->CollisionDetection(mBC);
	MapManager* MM = GetGame()->GetMapManager();
	std::pair<int, int> rowCol = MM->GetRowCol(GetPosition());
	if (mCurrRowCol != rowCol) {
		mCurrRowCol = rowCol;
		MM->ResetMap();

		for (Monster* m : GetGame()->GetMonsters()) {
			MM->PathFinding(m->GetPosition(), GetPosition());
		}
		MM->PrintMap();
	}
	mCurrCoolTime -= deltaTime;
	Attack();
}

void Player::ActorInput(const uint8_t* keyState)
{
	// 임시 코드
	if (keyState[SDL_SCANCODE_UP]) {
		mAC->SetCurrAnim("Up");
		mFace = Vector2::Up;
	}
	if (keyState[SDL_SCANCODE_DOWN]) {
		mAC->SetCurrAnim("Down");
		mFace = Vector2::Down;
	}

	if (keyState[SDL_SCANCODE_LEFT]) {
		mAC->SetCurrAnim("Left");
		mFace = Vector2::Left;
	}
	if (keyState[SDL_SCANCODE_RIGHT]) {
		mAC->SetCurrAnim("Right");
		mFace = Vector2::Right;
	}
}

void Player::OnCollision(ColliderComponent* other)
{
	switch (other->GetOwner()->GetLayer()){
	case EMonster:
		Hit(5);
		break;
	case EProp:
		if(other->GetType() == Component::kBoxComponent)
			ResolveCollision(static_cast<BoxComponent*>(other)->GetWorldBox());
		break;
	default:
		break;
	}
}

void Player::ResolveCollision(const AABB& other)
{
	const AABB& box = mBC->GetWorldBox();

	float dx1 = other.mMax.x - box.mMin.x;
	float dx2 = other.mMin.x - box.mMax.x;
	float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;

	float dy1 = other.mMax.y - box.mMin.y;
	float dy2 = other.mMin.y - box.mMax.y;
	float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;

	Vector2 pos = GetPosition();
	if (Math::Abs(dx) < Math::Abs(dy)) pos.x += dx;
	else pos.y += dy;

	SetPosition(pos);
	mBC->OnUpdateWorldTransform();
	ComputeWorldTransform();
}

void Player::Attack()
{
	if (mCurrCoolTime < 0.0f) {
		mCurrCoolTime = mAttackCoolTime;
		Weapon* w = new Weapon(GetGame(), this);
	}
}

void Player::Hit(float damage)
{
	if (!mIsInvincible) {
		mHP -= damage;
		mCurrITime = 0.0f;
		mIsInvincible = true;
	}
}

void Player::Death()
{
}

