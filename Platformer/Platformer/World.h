#ifndef WORLD_H
#define WORLD_H

#include "ComponentManager.h"
#include "Actor.h"

class World
{
public:

	void InitializeWorld(ComponentManager* compManager);
	void Update();

private:
	void InitializeGround();
	void InitializeBackGround();

private:
	ComponentManager* componentManager;
	std::vector<Actor*> worldObjects;
	std::vector<sf::Texture*> Textures;
	std::vector<sf::Sprite*> tiles;


private:

	sf::Texture* groundTileTexture;
	sf::Texture* backgroundTexture;
	sf::Sprite* background;
};

#endif // !WORLD_H