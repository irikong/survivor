#pragma once
#include <string>
#include <unordered_map>
#include "SDL/SDL.h"
#include "Math.h"

struct PointLight {
	Vector3 mPosition;
	Vector3 mColor;
	float mFallOffRange;
};

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
	void SetAmbientLight(Vector3 color);
	void AddPointLight(PointLight* pt);
	void RemovePointLight(PointLight* pt);
	void InitPointLight();

	class Texture* GetTexture(const std::string& fileName);
	float GetScreenWidth() const { return mWindowWidth; }
	float GetScreenHeight() const { return mWindowHeight; }

private:
	const int MAX_POINTLIGHT;

	bool LoadShaders();
	void CreateSpriteVerts();

	class Game* mGame;

	std::vector<PointLight*> mPointLights;

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

