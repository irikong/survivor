#pragma once
#include <string>
#include <unordered_map>
#include "SDL/SDL.h"
#include "Math.h"

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();

	bool Initialize(float windowWidth, float windowHeight);
	void Shutdown();
	void UnloadData();
	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void AddTileMap(class TileMapComponent* tilemap);
	void RemoveTileMap(class TileMapComponent* tilemap);
	void SetAmbientLight(float r, float g, float b);

	class Texture* GetTexture(const std::string& fileName);
	float GetScreenWidth() const { return mWindowWidth; }
	float GetScreenHeight() const { return mWindowHeight; }

private:
	bool LoadShaders();
	void CreateSpriteVerts();

	class Game* mGame;

	std::unordered_map<std::string, class Texture*> mTextures;
	std::vector<class SpriteComponent*> mSprites;
	std::vector<class TileMapComponent*> mTileMaps;

	std::unordered_map<int, class Shader*> mShaders;
	class Shader* mSpriteShader;
	class Shader* mTileShader;
	class VertexArray* mSpriteVerts;

	SDL_Window* mWindow;
	SDL_GLContext mContext;

	float mWindowWidth;
	float mWindowHeight;
};

