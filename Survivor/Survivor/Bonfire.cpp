#include "Bonfire.h"
#include "SpriteComponent.h"
#include "PointLightComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"

Bonfire::Bonfire(Game* game, float range, float fallOffRange) : 
	Actor(game)
{
	mSC = new SpriteComponent(this);
	mSC->SetTexture(game->GetRenderer()->GetTexture("Bonfire.png"));

	mPointLightComp = new PointLightComponent(this);
	mPointLightComp->SetLightColor(Vector3(0.9f, 0.6f, 0.1f));
	mPointLightComp->SetLightRange(range);
	mPointLightComp->SetLightFallOffRange(fallOffRange);
	mPointLightComp->SetFlickState(true);
}
