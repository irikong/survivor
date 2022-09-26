#pragma once
#include <vector>
#include "SDL/SDL.h"

class Game {
public:
	Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void AddMonster(class Monster* monster);
	void RemoveMonster(class Monster* monster);

	class Renderer* GetRenderer() { return mRenderer; }
	class Physics2D* GetPhysics2D() { return mPhysics2D; }
	class Player* GetPlayer() { return mPlayer; }
	class MapManager* GetMapManager() { return mMapManager; }
	std::vector<class Monster*>& GetMonsters() { return mMonsters; }

private:
	const int MIN_TICK;
	const float MAX_DELTA_TIME;

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void LoadTestData();
	void UnloadData();

	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	class Renderer* mRenderer;
	class Physics2D* mPhysics2D;

	class Player* mPlayer;
	class MapManager* mMapManager;

	std::vector<class Monster*> mMonsters;
};