#include "Creature.h"

Creature::Creature(Game* game, int hp, float speed) : 
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

void Creature::Hit(int damage)
{
}

void Creature::Death()
{
}
