#pragma once
#include "Actor.h"

class Bonfire : public Actor
{
public:
	Bonfire(class Game* game, float range, float fallOffRange);
	~Bonfire() = default;

private:
	class SpriteComponent* mSC;
	class PointLightComponent* mPointLightComp;
};
