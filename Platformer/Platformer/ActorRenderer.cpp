#include "ActorRenderer.h"
#include "Collider.h"
#include "Player.h"
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
		sprites[i].setTexture(sf::Texture());
		sprites[i] = sf::Sprite();
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
			GLOBAL::WINDOW->draw(sprites[i]);
		}
	}
}

void ActorRenderer::AddSprite(const sf::Sprite& spriteToSet)
{
	sprites.push_back(spriteToSet);
}