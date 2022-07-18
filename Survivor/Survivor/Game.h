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
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

private:
	const int MIN_TICK;
	const float MAX_DELTA_TIME;

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadShaders();

	SDL_Window* mWindow;
	SDL_GLContext mContext;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	std::vector<class SpriteComponent*> mSprites;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;
};