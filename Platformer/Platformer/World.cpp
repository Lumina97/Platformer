#include "World.h"
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Debug.h"
#include "Log.h"
using namespace sf;

World::~World()
{	
	delete(background);
	for (size_t i = 0; i < worldObjects.size(); i++)
	{
		componentManager->Destroy(worldObjects[i]);
	}
}

void World::InitializeWorld(ComponentManager* compManager)
{
	componentManager = compManager;
	platformIndex = 0;
	groundTileTexture.loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Assets/Tiles.png");

	InitializeBackGround();
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

	CreatePlatform(position, 3000);
}

void World::InitializeBackGround()
{
	if (!backgroundTexture.loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Background/Background.png"))
	{
		ENGINE_LOG_ERROR("Error loading texture from file!");
		return;
	}

	background = new sf::Sprite();
	background->setTexture(backgroundTexture);
	background->setPosition(GLOBAL::CAMERA->getCenter().x - GLOBAL::CAMERA->getSize().x / 2.f,
		GLOBAL::CAMERA->getCenter().y - GLOBAL::CAMERA->getSize().y / 2.f);

	background->setScale(GLOBAL::CAMERA->getSize().x / background->getLocalBounds().width,
		GLOBAL::CAMERA->getSize().y / background->getLocalBounds().height);
}

void World::CreatePlatform(sf::Vector2f position, float length, float height)
{
	Vector2f size = Vector2f(length, height);
	std::string name = "platform" + std::to_string(platformIndex);

	Actor* platform = componentManager->CreateNewActor<Actor>(position, size, name,
		ComponentType::collider | ComponentType::actorRenderer);

	platform->setOrigin(Vector2f(size.x / 2, size.y));

	ActorRenderer* renderer = platform->GetComponent<ActorRenderer>();	

	float spriteSizeX = 26;
	int iterations = size.x / spriteSizeX;
	iterations++;
	for (int i = 0; i < iterations; i++)
	{
		sf::Sprite* groundTile = new sf::Sprite();
		groundTile->setTexture(groundTileTexture);
		groundTile->setTextureRect(sf::IntRect(spriteSizeX, 10, spriteSizeX, 70));
		sf::Vector2f pos = platform->getPosition() - platform->getOrigin();
		pos.x += i * spriteSizeX;
		groundTile->setPosition(pos);

		renderer->AddSprite(groundTile);
	}
	worldObjects.push_back(platform);
	platformIndex++;
}