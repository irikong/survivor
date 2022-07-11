#include "Game.h"
#include "GL/glew.h"

Game::Game() :
	mWindow(nullptr),
	mIsRunning(true)
{
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// OpenGL ¼³Á¤
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Survivor", 200, 200, 1024, 768, SDL_WINDOW_OPENGL);
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
}

void Game::GenerateOutput()
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(mWindow);
}
