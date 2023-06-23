#ifndef WORLD_H
#define WORLD_H

#include "ComponentManager.h"
#include "Actor.h"

class World
{
public:

	void InitializeWorld(ComponentManager* compManager);

private:
	void InitializeGround();

private:
	ComponentManager* componentManager;
	std::vector<Actor*> worldObjects;
	std::vector<sf::Texture*> Textures;
	std::vector<sf::Sprite*> tiles;
};

#endif // !WORLD_H