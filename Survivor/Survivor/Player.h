#pragma once
#include "Actor.h"
class Player : public Actor
{
public:
	Player(class Game* game);
	~Player() = default;

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

private:
	class SpriteComponent* mSC;
	class InputComponent* mIC;
};

