#pragma once
#include "Actor.h"

class Bonfire : public Actor
{
public:
	Bonfire(class Game* game, float range);
	~Bonfire() = default;

private:
	class SpriteComponent* mSC;
	class PointLightComponent* mPointLightComp;
	class PointLightComponent* mOutLight;
};

