#include "TileMapComponent.h"
#include <fstream>
#include "Game.h"
#include "Actor.h"
#include "Texture.h"
#include "Shader.h"
#include "Renderer.h"

TileMapComponent::TileMapComponent(Actor* owner, int fWidth, int fHeight, int drawOrder) :
	AtlasComponent(owner, fWidth, fHeight, drawOrder),
	MAP_ROW(),
	MAP_COL()
{
	
}

void TileMapComponent::Draw(Shader* shader)
{
	if (mTexture) {
		Matrix4 texScale = Matrix4::CreateScale(static_cast<float>(mTexWidth / FRAMES_PER_ROW), static_cast<float>(mTexHeight / FRAMES_PER_COL), 1.0f);
		Matrix4 world = texScale * mOwner->GetWorldTransform();
		
		shader->SetIntUniform("uTPR", FRAMES_PER_ROW);
		shader->SetIntUniform("uTPC", FRAMES_PER_COL);
		shader->SetFloatUniform("uAlpha", mAlpha);
		mTexture->SetActive();

		for (auto& tile : mTiles) {
			if (tile.texIdx == -1) continue;

			shader->SetMatrixUniform("uWorldTransform", world * Matrix4::CreateTranslation(static_cast<float>(tile.posX), static_cast<float>(tile.posY), 0.f));
			shader->SetIntUniform("uIdx", tile.texIdx);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}
}

void TileMapComponent::LoadTileMap(const std::string& filePath, int mapRow, int mapCol)
{
	MAP_ROW = mapRow;
	MAP_COL = mapCol;

	std::fstream fs;
	fs.open(filePath, std::ios::in);

	std::string line;
	while (!fs.eof()) {
		getline(fs, line, ',');

		size_t lf = line.find('\n');
		if (lf != std::string::npos) {
			std::string l(line.substr(0, lf));
			mTiles.emplace_back(std::stoi(l), (mTiles.size() % MAP_COL) * FRAME_WIDTH, (mTiles.size() / MAP_COL) * -FRAME_HEIGHT);

			if (lf != line.size() - 1) {
				std::string r(line.substr(lf + 1));
				mTiles.emplace_back(std::stoi(r), (mTiles.size() % MAP_COL) * FRAME_WIDTH, (mTiles.size() / MAP_COL) * -FRAME_HEIGHT);
			}
		}
		else {
			mTiles.emplace_back(std::stoi(line), (mTiles.size() % MAP_COL) * FRAME_WIDTH, (mTiles.size() / MAP_COL) * -FRAME_HEIGHT);
		}
	}

	fs.close();
}
