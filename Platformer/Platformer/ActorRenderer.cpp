#include "ActorRenderer.h"
#include "Actor.h"
#include "Collider.h"
#include "Animator.h"
#include "Globals.h"

ActorRenderer::ActorRenderer( Actor* parentActor)
{
	this->parentActor = parentActor;
	this->type = ComponentType::actorRenderer;

	setOrigin(parentActor->getOrigin());
	setPosition(parentActor->getPosition());	
}

ActorRenderer::~ActorRenderer()
{
	//clear all sprite texture resources
	for (int i = 0; i < sprites.size(); i++)
	{
		delete(sprites[i]);
	}
	sprites.clear();
}

void ActorRenderer::UpdateComponent()
{
	Component::UpdateComponent();
	if (sprites.size() > 0)
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			GLOBAL::WINDOW->draw(*sprites[i]);
		}
	}
}

void ActorRenderer::AddSprite(sf::Sprite* spriteToSet)
{
	sprites.push_back(spriteToSet);
}