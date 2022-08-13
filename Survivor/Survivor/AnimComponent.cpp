#include "AnimComponent.h"
#include "Math.h"
#include "Actor.h"
#include "Shader.h"
#include "Texture.h"

AnimComponent::AnimComponent(Actor* owner, int fWidth, int fHeight, int drawOrder) : 
	AtlasComponent(owner, fWidth, fHeight, drawOrder),
	mAnimFPS(0.0),
	mCurrFrame(0.0),
	mCurrAnim()
{

}

void AnimComponent::Update(float deltaTime)
{
	if (mCurrAnim.empty()) return;

	mCurrFrame += mAnimFPS * deltaTime;
	while (mCurrFrame >= mAnims[mCurrAnim].size()) {
		mCurrFrame -= mAnims[mCurrAnim].size();
	}
}

void AnimComponent::Draw(Shader* shader)
{
	if (mCurrAnim.empty()) return;

	if (mTexture) {
		Matrix4 texScale = Matrix4::CreateScale(static_cast<float>(mTexWidth / FRAMES_PER_ROW), static_cast<float>(mTexHeight / FRAMES_PER_COL), 1.0f);
		Matrix4 world = texScale * mOwner->GetWorldTransform();
		shader->SetMatrixUniform("uWorldTransform", world);
		shader->SetIntUniform("uTPR", FRAMES_PER_ROW);
		shader->SetIntUniform("uTPC", FRAMES_PER_COL);
		shader->SetIntUniform("uIdx", mAnims[mCurrAnim][static_cast<int>(mCurrFrame)]);
		shader->SetFloatUniform("uAlpha", mAlpha);

		mTexture->SetActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void AnimComponent::AddAnim(const std::string& animName, int startFrame, int endFrame)
{
	auto iter = mAnims.find(animName);
	if (iter != mAnims.end()) {
		(*iter).second.clear();
	}

	for (int f = startFrame; f <= endFrame; f++) {
		mAnims[animName].push_back(f);
	}
}

void AnimComponent::AppendAnim(const std::string& animName, int startFrame, int endFrame)
{
	for (int f = startFrame; f <= endFrame; f++) {
		mAnims[animName].push_back(f);
	}
}

void AnimComponent::SetCurrAnim(const std::string& animName)
{
	mCurrAnim = animName;
	mCurrFrame = 0.0f;
}
