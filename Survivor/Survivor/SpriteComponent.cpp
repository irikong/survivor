#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include "Shader.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) :
	Component(owner),
	mTexture(nullptr),
	mDrawOrder(drawOrder),
	mTexWidth(100), // TODO: Texture 매핑 추가 후 0으로 변경할 것
	mTexHeight(100)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	Matrix4 texScale = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
	Matrix4 world = texScale * mOwner->GetWorldTransform();

	shader->SetMatrixUniform("uWorldTransform", world);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}

