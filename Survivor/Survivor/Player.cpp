#include "Player.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "AnimComponent.h"
#include "InputComponent.h"
#include "Collision.h"
#include "CircleComponent.h"
#include "Physics2D.h"

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

	Circle circle(Vector2::Zero, 32);
	mCC = new CircleComponent(this, circle);
}

void Player::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	//for (auto collider : GetGame()->GetPhysics2D()->GetColliders()) {
	//	if ((collider != mCC) && Intersect(mCC->GetWorldCircle(), collider->())) {
	//		// TODO: 충돌 처리
	//	}
	//}
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
