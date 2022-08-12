#pragma once
#include "AtlasComponent.h"
#include <string>
#include <unordered_map>

class AnimComponent : public AtlasComponent
{
public:
	AnimComponent(class Actor* owner, int drawOrder = 100);
	~AnimComponent() = default;

	void Update(float deltaTime) override;
	void Draw(class Shader* shader) override;

	void AddAnim(const std::string& animName, int startFrame, int endFrame);
	void AppendAnim(const std::string& animName, int startFrame, int endFrame);

	Type GetType() const override { return kAnimComponent; }
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	void SetCurrAnim(const std::string& animName);

private:
	float mAnimFPS;
	float mCurrFrame;
	std::string mCurrAnim;

	std::unordered_map<std::string, std::vector<int>> mAnims;
};

