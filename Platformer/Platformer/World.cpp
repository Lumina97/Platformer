#include "World.h"
#include "SFML/Graphics.hpp"
#include "Globals.h"

using namespace sf;

void World::InitializeWorld(ComponentManager* compManager)
{
	componentManager = compManager;
	
	Vector2f position = Vector2f(GLOBAL::ScreenSize.x / 2 , GLOBAL::ScreenSize.y);
	Vector2f size = Vector2f(GLOBAL::ScreenSize.x , 100 );

	Actor* ground = componentManager->CreateNewActor<Actor>(position, size, "GroundPlane",ComponentFlags::collision | ComponentFlags::rendering);
	ground->setOrigin(Vector2f( size.x / 2, size.y));

	worldObjects.push_back(ground);
}