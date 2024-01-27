#include "TestScene.h"
#include "Globals.h"
#include "time.h"
#include "Log.h"
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Debug.h"
#include "ComponentManager.h"
#include "Actor.h"
#include "tmxlite/ObjectGroup.hpp"
#include "tmxlite/TileLayer.hpp"
#include "tmxlite/LayerGroup.hpp"

void TestScene::InitializeScene(ComponentManager* compManager)
{
	this->componentManager = compManager;
	try
	{
		map.load("assets/Test.tmx");
		mapLayers.push_back(new MapLayer(map, 1));

		const auto& layers = map.getLayers();
		for (const auto& layer : layers)
		{
			if (layer->getType() == tmx::Layer::Type::Object)
			{
				const auto& objects = layer->getLayerAs<tmx::ObjectGroup>().getObjects();				
				for (const auto& object : objects)
				{
					sf::Vector2f position(object.getPosition().x, object.getPosition().y);
					sf::Vector2f size(object.getAABB().width, object.getAABB().height);
					Actor* actor = componentManager->CreateNewActor<Actor>(position, size, object.getName(), ComponentType::collider);	
				}
			}
		}
	}
	catch (const std::exception&)
	{
		ENGINE_LOG_ERROR("There was an error loading the map! TestScene!");
	}
}

void TestScene::UnloadScene()
{
	delete(mapLayers[0]);
	componentManager->Destroy(mapActor);
}

void TestScene::UpdateScene()
{


	float x = 0, y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		x = -1000 * TIME::DeltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		x = 1000 * TIME::DeltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		y = -1000 * TIME::DeltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		y = 1000 * TIME::DeltaTime;


	GLOBAL::CAMERA->move(sf::Vector2f(x, y));
	GLOBAL::WINDOW->setView(*GLOBAL::CAMERA);

	componentManager->UpdateComponents();
	GLOBAL::WINDOW->draw(*mapLayers[0]);
}

void TestScene::ReloadScene()
{

}
