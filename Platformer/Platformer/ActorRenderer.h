#ifndef ACTOR_RENDERER_H
#define ACTOR_RENDERER_H

#define DEBUG 1	

#include "SFML/Graphics.hpp"
#include "Actor.h"
#include "Component.h"

class ActorRenderer: public Component
{
public:
	ActorRenderer(std::string textureFilePath, sf::RenderWindow* window , Actor* parentActor);
	ActorRenderer(sf::Vector2f size, sf::RenderWindow* window , Actor* parentActor);

	virtual void UpdateComponent();

private:

	sf::Texture spriteTexture;
	sf::Sprite sprite;
	std::string textureFilePath;
	sf::RectangleShape shape;
	sf::RectangleShape debug;
	sf::RenderWindow* window = nullptr;
};


#endif // !ACTOR_RENDERER_H