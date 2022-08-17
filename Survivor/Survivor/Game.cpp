#include "Game.h"
#include "GL/glew.h"
#include "Actor.h"
#include "Component.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "TileMapComponent.h"
#include "Renderer.h"
#include "Constants.h"
#include "Player.h"
#include "Physics2D.h"
#include "CircleComponent.h"
#include "BoxComponent.h"

Game::Game() :
	MIN_TICK(16),
	MAX_DELTA_TIME(0.05f),
	mTicksCount(),
	mIsRunning(true),
	mUpdatingActors(false),
	mRenderer(nullptr),
	mPhysics2D(nullptr)
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(1024.0f, 768.0f)) {
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
	Player* player = new Player(this);

	Actor* b = new Actor(this);
	b->SetPosition(Vector2(-mRenderer->GetScreenWidth() / 2, mRenderer->GetScreenHeight() / 2));
	TileMapComponent* tm1 = new TileMapComponent(b, 32, 32);
	tm1->SetTexture(mRenderer->GetTexture("Grass1.png"));
	tm1->LoadTileMap(std::string(Path::ASSETS) + "Layer1.csv", 16, 16);
	TileMapComponent* tm2 = new TileMapComponent(b, 32, 32);
	tm2->SetTexture(mRenderer->GetTexture("Dirt2.png"));
	tm2->LoadTileMap(std::string(Path::ASSETS) + "Layer2.csv", 16, 16);
	tm2->SetAlpha(0.7f);

	Actor* c = new Actor(this);
	c->SetPosition(Vector2(-300, 250));
	SpriteComponent* sc = new SpriteComponent(c, 15);
	sc->SetTexture(mRenderer->GetTexture("Circle.png"));
	CircleComponent* cc = new CircleComponent(c, Circle(Vector2::Zero, sc->GetTexWidth() / 2.0f));

	Actor* d = new Actor(this);
	d->SetPosition(Vector2(200, 200));
	sc = new SpriteComponent(d, 15);
	sc->SetTexture(mRenderer->GetTexture("Box.png"));
	BoxComponent* bc = new BoxComponent(d, AABB(Vector2(-16, -16), Vector2(16, 16)));
}

void Game::UnloadData()
{
	while (!mActors.empty())
		delete mActors.back();

	if (mRenderer) mRenderer->UnloadData();
}

