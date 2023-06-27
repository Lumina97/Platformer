#include "World.h"
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Debug.h"
#include "Log.h"
using namespace sf;

void World::InitializeWorld(ComponentManager* compManager)
{
	componentManager = compManager;
	backgroundTexture = new sf::Texture();
	groundTileTexture = new sf::Texture();
	InitializeGround();
}

void World::Update()
{
	if (background == nullptr) return;
	background->setPosition(GLOBAL::CAMERA->getCenter().x - GLOBAL::CAMERA->getSize().x / 2.f,
		GLOBAL::CAMERA->getCenter().y - GLOBAL::CAMERA->getSize().y / 2.f);
	GLOBAL::WINDOW->draw(*background);
}

void World::InitializeGround()
{
	Vector2f position = Vector2f(GLOBAL::ScreenSize.x / 2, GLOBAL::ScreenSize.y);
	Vector2f size = Vector2f(2000, 80);

	Actor* ground = componentManager->CreateNewActor<Actor>(position, size, "GroundTile", ComponentType::collider | ComponentType::actorRenderer);
	ground->setOrigin(Vector2f(size.x / 2, size.y));
	InitializeBackGround();

	groundTileTexture->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Assets/Tiles.png");

	float spriteSizeX = 26;
	int iterations = size.x / spriteSizeX;
	iterations++;
	for (int i = 0; i < iterations; i++)
	{
		sf::Sprite* groundTile = new sf::Sprite();
		groundTile->setTexture(*groundTileTexture);
		groundTile->setTextureRect(sf::IntRect(spriteSizeX, 10, spriteSizeX, 70));
		sf::Vector2f position = ground->getPosition() - ground->getOrigin();
		position.x += i * spriteSizeX;
		groundTile->setPosition(position);	

		Textures.push_back(groundTileTexture);
		ground->GetComponent<ActorRenderer>()->AddSprite(*groundTile);
	}
	worldObjects.push_back(ground);
}

void World::InitializeBackGround()
{
	if (!backgroundTexture->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Background/Background.png"))
	{
		ENGINE_LOG_ERROR("Error loading texture from file!");
		return;
	}

	background = new sf::Sprite();
	background->setTexture(*backgroundTexture);
	background->setPosition(GLOBAL::CAMERA->getCenter().x - GLOBAL::CAMERA->getSize().x / 2.f,
		GLOBAL::CAMERA->getCenter().y - GLOBAL::CAMERA->getSize().y / 2.f);

	background->setScale(GLOBAL::CAMERA->getSize().x / background->getLocalBounds().width,
		GLOBAL::CAMERA->getSize().y / background->getLocalBounds().height);
}