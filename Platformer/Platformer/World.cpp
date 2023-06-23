#include "World.h"
#include "SFML/Graphics.hpp"
#include "Globals.h"

using namespace sf;

void World::InitializeWorld(ComponentManager* compManager)
{
	componentManager = compManager;
	InitializeGround();
}

void World::InitializeGround()
{
	Vector2f position = Vector2f(GLOBAL::ScreenSize.x / 2, GLOBAL::ScreenSize.y);
	Vector2f size = Vector2f(GLOBAL::ScreenSize.x, 100);

	Actor* ground = componentManager->CreateNewActor<Actor>(position, size, "GroundTile", ComponentType::collider | ComponentType::actorRenderer);
	ground->setOrigin(Vector2f(size.x / 2, size.y));

	sf::Texture* tiles = new sf::Texture();
	tiles->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Assets/Tiles.png");

	int interations = size.x / 89.5f;
	interations++;
	for (int i = 0; i < interations; i++)
	{
		sf::Sprite* groundTile = new sf::Sprite();
		groundTile->setTexture(*tiles);
		groundTile->setTextureRect(sf::IntRect(0, 0, 80, 80));
		groundTile->setScale(1.12f, 1.12f);
		sf::Vector2f position = ground->getPosition();
		position.x += i * 89.5f;
		groundTile->setPosition(position);
		groundTile->setOrigin(ground->getOrigin());

		Textures.push_back(tiles);
		ground->GetComponent<ActorRenderer>()->AddSprite(*groundTile);
	}
	worldObjects.push_back(ground);
}