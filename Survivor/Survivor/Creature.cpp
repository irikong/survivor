#include "Creature.h"

Creature::Creature(Game* game, float hp, float speed) : 
	Actor(game),
	mHP(hp),
	mSpeed(speed)
{

}

void Creature::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
}

void Creature::Attack()
{
}

void Creature::Hit(float damage)
{
}

void Creature::Death()
{
}
