#pragma once
#include "Actor.h"
#include "Monster.h"

class MonsterSpawner : public Actor
{
public:
	MonsterSpawner(class Game* game);
	~MonsterSpawner() = default;

	void UpdateActor(float deltaTime) override;

	template <typename T>
	T* Spawn() {
		return new T(GetGame());
	}

private:
	Vector2 GetRandomSpawnPos();

	//bool mIsActive;
	float mSpawnInterval;
	float mNextSpawn;
};
