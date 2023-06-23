#ifndef ACTOR_RENDERER_H
#define ACTOR_RENDERER_H



#include "SFML/Graphics.hpp"
#include "Actor.h"
#include "Component.h"

class ActorRenderer: public Component
{
public:
	ActorRenderer(Actor* parentActor);
	~ActorRenderer();
	virtual void UpdateComponent();
	/// <summary>
	/// Adds a sprite and takes ownership of it
	/// </summary>
	/// <param name="spriteToSet"></param>
	void AddSprite(const sf::Sprite& spriteToSet);

private:

	sf::Texture spriteTexture;
	std::vector<sf::Sprite> sprites;
};


#endif // !ACTOR_RENDERER_H