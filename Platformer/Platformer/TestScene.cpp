#include "TestScene.h"
#include "Globals.h"
#include "time.h"
#include "Log.h"
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Debug.h"
#include "ComponentManager.h"
#include "Actor.h"


void TestScene::InitializeScene(ComponentManager* compManager)
{
	try
	{
		map.load("assets/Test.tmx");

		layers.push_back(new MapLayer(map, 0));
		window = GLOBAL::WINDOW;
		componentManager = compManager;
		sf::Vector2 pos(layers[0]->getGlobalBounds().left, layers[0]->getGlobalBounds().top);
		sf::Vector2 size(layers[0]->getGlobalBounds().width, layers[0]->getGlobalBounds().height);

		mapActor = componentManager->CreateNewActor<Actor>(pos, size, "map", ComponentType::collider);
		mapActor->setOrigin(GLOBAL::ScreenSize.x / 2, GLOBAL::ScreenSize.y);
	}
	catch (const std::exception&)
	{
		ENGINE_LOG_ERROR("There was an error loading the map! TestScene!");
	}
}

void TestScene::UnloadScene()
{
	delete(layers[0]);
	componentManager->Destroy(mapActor);
}

void TestScene::UpdateScene()
{
	if (window == nullptr)
	{
		ENGINE_LOG_ERROR("Window was not defined! TestScene.cpp");
		return;
	}
	int x = 0, y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		x = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		x = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		y = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		y = 1;

	GLOBAL::CAMERA->move(sf::Vector2f(x, y));
	GLOBAL::WINDOW->setView(*GLOBAL::CAMERA);

	componentManager->UpdateComponents();
	layers[0]->update(TIME::SFDeltaTime);
	window->draw(*layers[0]);



}

void TestScene::ReloadScene()
{

}
