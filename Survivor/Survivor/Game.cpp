#include "Game.h"
#include "GL/glew.h"
#include "Actor.h"
#include "Component.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Constants.h"
#include "Player.h"
#include "Physics2D.h"
#include "CircleComponent.h"
#include "BoxComponent.h"
#include "MapManager.h"
#include "Monster.h"
#include "Skeleton.h"
#include "Ghost.h"
#include "MonsterSpawner.h"

Game::Game() :
	MIN_TICK(16),
	MAX_DELTA_TIME(0.05f),
	mTicksCount(),
	mIsRunning(true),
	mUpdatingActors(false),
	mRenderer(nullptr),
	mPhysics2D(nullptr),
	mPlayer(nullptr),
	mMapManager(nullptr)
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(1024.0f, 800.0f)) {
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	mPhysics2D = new Physics2D(this);

	LoadTestData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	UnloadData();
	if (mRenderer) mRenderer->Shutdown();
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddMonster(Monster* monster)
{
	mMonsters.emplace_back(monster);
}

void Game::RemoveMonster(Monster* monster)
{
	auto iter = std::find(mMonsters.begin(), mMonsters.end(), monster);
	if (iter != mMonsters.end()) {
		mMonsters.erase(iter);
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + MIN_TICK));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > MAX_DELTA_TIME)
		deltaTime = MAX_DELTA_TIME;
	mTicksCount = SDL_GetTicks();

	mUpdatingActors = true;
	for (Actor* actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (Actor* pendingActor : mPendingActors) {
		pendingActor->ComputeWorldTransform();
		mActors.emplace_back(pendingActor);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (Actor* actor : mActors) {
		if (actor->GetState() == Actor::State::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	for (Actor* deadActor : deadActors) {
		delete deadActor;
	}
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::LoadTestData()
{
	mPlayer = new Player(this, 100.0f, 200.0f);
	mMapManager = new MapManager(this);

	MonsterSpawner* monsterSpawner = new MonsterSpawner(this);
}

void Game::UnloadData()
{
	while (!mActors.empty())
		delete mActors.back();

	if (mRenderer) mRenderer->UnloadData();
}

