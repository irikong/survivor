#pragma once
#include <vector>
#include <unordered_map>
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

	class Texture* GetTexture(const std::string& fileName);

private:
	const int MIN_TICK;
	const float MAX_DELTA_TIME;
	const std::string ASSETS_PATH;
	const std::string SHADERS_PATH;

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void CreateSpriteVerts();
	bool LoadShaders();
	void LoadTestData();

	static int windowWidth;
	static int windowHeight;

	SDL_Window* mWindow;
	SDL_GLContext mContext;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	std::vector<class SpriteComponent*> mSprites;
	std::unordered_map<std::string, class Texture*> mTextures;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;
};