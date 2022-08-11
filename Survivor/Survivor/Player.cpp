#include "Player.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Renderer.h"
#include "Texture.h"

Player::Player(Game* game) :
	Actor(game)
{
	SetRotation(Math::PI / 2);

	mSC = new SpriteComponent(this);
	mSC->SetTexture(game->GetRenderer()->GetTexture("Test.png"));

	mIC = new InputComponent(this);
	mIC->SetUpKey(SDL_SCANCODE_UP);
	mIC->SetDownKey(SDL_SCANCODE_DOWN);
	mIC->SetLeftKey(SDL_SCANCODE_LEFT);
	mIC->SetRightKey(SDL_SCANCODE_RIGHT);
	mIC->SetSpeed(300.0f);
}

void Player::UpdateActor(float deltaTime)
{
}

void Player::ActorInput(const uint8_t* keyState)
{
}
