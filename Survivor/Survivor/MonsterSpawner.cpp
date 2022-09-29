#include "MonsterSpawner.h"
#include "Game.h"
#include "Ghost.h"
#include "Skeleton.h"
#include "Random.h"
#include "Player.h"
#include "MapManager.h"

MonsterSpawner::MonsterSpawner(Game* game) :
	Actor(game),
	mSpawnInterval(2.0f),
	mNextSpawn(0.0f)
{
	MapManager* mm = game->GetMapManager();
	mSpawnDistance = mm->GetTileWidth() * (mm->GetMapRow() / 2 - 1);
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
	if (playerDir == Vector2::Zero) playerDir = Vector2::Right;
	else playerDir.Normalize();

	float theta = Math::Acos(Vector2::Dot(Vector2::Right, playerDir));
	if (playerDir.y < 0) theta = Math::TWOPI - theta;

	theta += Random::GetFloatRange(0, Math::PI) + Math::PIDIV2;

	Vector2 pos(mSpawnDistance * Math::Cos(theta), mSpawnDistance * Math::Sin(theta));

	return pos;
}
