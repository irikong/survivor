#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "TileMapComponent.h"
#include "Constants.h"

Renderer::Renderer(Game* game) :
	mGame(game),
	mSpriteShader(nullptr),
	mTileShader(nullptr),
	mSpriteVerts(nullptr),
	mWindow(),
	mContext(),
	mWindowWidth(0),
	mWindowHeight(0)
{

}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(float windowWidth, float windowHeight)
{
	mWindowWidth = windowWidth;
	mWindowHeight = windowHeight;

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

	mWindow = SDL_CreateWindow("Survivor", 200, 200, (int)mWindowWidth, (int)mWindowHeight, SDL_WINDOW_OPENGL);
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

	return true;
}

void Renderer::Shutdown()
{
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	mTileShader->Unload();
	delete mTileShader;

	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	for (auto& t : mTextures) {
		t.second->Unload();
		delete t.second;
	}
	mTextures.clear();
}

void Renderer::Draw()
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mSpriteVerts->SetActive();

	Component::Type shaderType = Component::Type::kComponent;
	for (const auto& sprite : mSprites) {
		if (shaderType != sprite->GetType()) {
			shaderType = sprite->GetType();
			mShaders[shaderType]->SetActive();
		}

		sprite->Draw(mShaders[shaderType]);
	}

	SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	int order = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	while (iter != mSprites.end()) {
		if (order < (*iter)->GetDrawOrder()) break;

		iter++;
	}

	mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end()) {
		mSprites.erase(iter);
	}
}

void Renderer::AddTileMap(TileMapComponent* tilemap)
{
	int order = tilemap->GetDrawOrder();
	auto iter = mTileMaps.begin();
	while (iter != mTileMaps.end()) {
		if (order < (*iter)->GetDrawOrder()) break;

		iter++;
	}

	mTileMaps.insert(iter, tilemap);
}

void Renderer::RemoveTileMap(TileMapComponent* tilemap)
{
	auto iter = std::find(mTileMaps.begin(), mTileMaps.end(), tilemap);
	if (iter != mTileMaps.end()) {
		mTileMaps.erase(iter);
	}
}

void Renderer::SetAmbientLight(Vector3 color)
{
	mSpriteShader->SetActive();
	mSpriteShader->SetVector3Uniform("uAmbientLight", color);
	mSpriteShader->SetVector3Uniform("uPointLight.mPosition", Vector3(40, 10, 0));
	mSpriteShader->SetVector3Uniform("uPointLight.mColor", Vector3(1, 1, 1));
	mSpriteShader->SetFloatUniform("uPointLight.mFallOffRange", 50);

	mTileShader->SetActive();
	mTileShader->SetVector3Uniform("uAmbientLight", color);
	mTileShader->SetVector3Uniform("uPointLight.mPosition", Vector3(40, 10, 0));
	mTileShader->SetVector3Uniform("uPointLight.mColor", Vector3(1, 1, 1));
	mTileShader->SetFloatUniform("uPointLight.mFallOffRange", 50);
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;

	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		tex = iter->second;
	}
	else {
		tex = new Texture();

		if (tex->Load(std::string(Path::ASSETS) + fileName)) {
			mTextures.emplace(fileName, tex);
		}
		else {
			delete tex;
			tex = nullptr;
		}
	}

	return tex;
}

bool Renderer::LoadShaders()
{
	std::string shadersPath = std::string(Path::SHADERS);

	// TODO: mShaders[] Shader 포인터 중복저장 개선

	mSpriteShader = new Shader();
	if (!mSpriteShader->Load(shadersPath + "Sprite.vert", shadersPath + "Sprite.frag")) return false;
	mSpriteShader->SetActive();
	Matrix4 viewProj = Matrix4::CreateViewProj(mWindowWidth, mWindowHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	mShaders[Component::Type::kSpriteComponent] = mSpriteShader;

	mTileShader = new Shader();
	if (!mTileShader->Load(shadersPath + "Atlas.vert", shadersPath + "Atlas.frag")) return false;
	mTileShader->SetActive();
	mTileShader->SetMatrixUniform("uViewProj", viewProj);
	mShaders[Component::Type::kAtlasComponent] = mTileShader;
	mShaders[Component::Type::kTileMapComponent] = mTileShader;
	mShaders[Component::Type::kAnimComponent] = mTileShader;

	return true;
}

void Renderer::CreateSpriteVerts()
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
