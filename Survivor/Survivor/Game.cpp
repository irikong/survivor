#include "Game.h"
#include "GL/glew.h"
#include "Actor.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"

int Game::windowWidth = 1024;
int Game::windowHeight = 768;

Game::Game() :
	MIN_TICK(16),
	MAX_DELTA_TIME(0.05f),
	ASSETS_PATH("Assets/"),
	SHADERS_PATH("Shaders/"),
	mContext(),
	mTicksCount(),
	mWindow(nullptr),
	mIsRunning(true),
	mUpdatingActors(false),
	mSpriteShader(nullptr),
	mSpriteVerts(nullptr)
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// OpenGL Setting
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Survivor", 200, 200, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);
	
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	glGetError();

	if (!LoadShaders()) {
		SDL_Log("Failed to load shaders.");
		return false;
	}

	CreateSpriteVerts();

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
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
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

void Game::AddSprite(SpriteComponent* sprite)
{
	int order = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	while (iter != mSprites.end()) {
		if (order < (*iter)->GetDrawOrder()) break;

		iter++;
	}

	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end()) {
		mSprites.erase(iter);
	}
}

Texture* Game::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;

	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		tex = iter->second;
	}
	else {
		tex = new Texture();

		if (tex->Load(ASSETS_PATH + fileName)) {
			mTextures.emplace(fileName, tex);
		}
		else {
			delete tex;
			tex = nullptr;
		}
	}

	return tex;
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
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();

	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	SDL_GL_SwapWindow(mWindow);
}

void Game::CreateSpriteVerts()
{
	// 3f(position), 2f(uv)
	float vertices[] = {
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, // LU
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // RU
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // RD
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // LD
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

bool Game::LoadShaders()
{
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load(SHADERS_PATH + "Sprite.vert", SHADERS_PATH + "Sprite.frag")) return false;
	mSpriteShader->SetActive();
	
	Matrix4 viewProj = Matrix4::CreateViewProj(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	return true;
}

void Game::LoadTestData()
{
	Actor* a = new Actor(this);
	SpriteComponent* sc = new SpriteComponent(a);
	sc->SetTexture(GetTexture("Test.png"));
}

