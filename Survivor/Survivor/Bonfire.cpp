#include "Bonfire.h"
#include "SpriteComponent.h"
#include "PointLightComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"

Bonfire::Bonfire(Game* game, float range) : 
	Actor(game)
{
	mSC = new SpriteComponent(this);
	mSC->SetTexture(game->GetRenderer()->GetTexture("Bonfire.png"));

	mPointLightComp = new PointLightComponent(this);
	mPointLightComp->SetLightColor(Vector3(0.9f, 0.6f, 0.1f));
	mPointLightComp->SetLightFallOffRange(range);
	mPointLightComp->SetFlickState(true);

	mOutLight = new PointLightComponent(this);
	mOutLight->SetLightColor(Vector3(0.2f, 0.2f, 0.2f));
	mOutLight->SetLightFallOffRange(1.5 * range);
}
