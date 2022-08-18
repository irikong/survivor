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

Player::Player(Game* game) :
	Actor(game)
{
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
	mIC->SetSpeed(300.0f);

	AABB box(Vector2(-16, -16), Vector2(16, 16));
	mBC = new BoxComponent(this, box);
}

void Player::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	GetGame()->GetPhysics2D()->CollisionDetection(mBC);
}

void Player::ActorInput(const uint8_t* keyState)
{
	// 임시 코드
	if (keyState[SDL_SCANCODE_UP]) {
		mAC->SetCurrAnim("Up");
	}
	if (keyState[SDL_SCANCODE_DOWN]) {
		mAC->SetCurrAnim("Down");
	}

	if (keyState[SDL_SCANCODE_LEFT]) {
		mAC->SetCurrAnim("Left");
	}
	if (keyState[SDL_SCANCODE_RIGHT]) {
		mAC->SetCurrAnim("Right");
	}
}

void Player::OnCollision(ColliderComponent* other)
{
	switch (other->GetType()){
	case Component::kCircleComponent:
		// Circle 처리
		break;
	case Component::kBoxComponent:
		ResolveCollision(dynamic_cast<BoxComponent*>(other)->GetWorldBox());
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

