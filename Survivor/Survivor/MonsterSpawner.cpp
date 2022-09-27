#include "MonsterSpawner.h"
#include "Game.h"
#include "Ghost.h"
#include "Skeleton.h"
#include "Random.h"
#include "Player.h"

MonsterSpawner::MonsterSpawner(Game* game) :
	Actor(game),
	mSpawnInterval(1.0f),
	mNextSpawn(0.0f)
{

}

void MonsterSpawner::UpdateActor(float deltaTime)
{
	mNextSpawn += deltaTime;
	if (mSpawnInterval < mNextSpawn) {
		Vector2 spawnPos = GetRandomSpawnPos();

		int r = Random::GetIntRange(0, 1);
		if(r) Spawn<Skeleton>()->SetPosition(spawnPos);
		else Spawn<Ghost>()->SetPosition(spawnPos);

		mNextSpawn -= mSpawnInterval;
	}
}

Vector2 MonsterSpawner::GetRandomSpawnPos()
{
	Vector2 playerDir = GetGame()->GetPlayer()->GetPosition() - Vector2::Zero;
	playerDir.Normalize();

	float theta = Math::Acos(Vector2::Dot(Vector2::Right, playerDir));
	if (playerDir.y < 0) theta = Math::TWOPI - theta;

	theta += Random::GetFloatRange(0, Math::PI) + Math::PIDIV2;

	Vector2 pos(240 * Math::Cos(theta), 240 * Math::Sin(theta));

	return pos;
}
