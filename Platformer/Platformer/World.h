#ifndef WORLD_H
#define WORLD_H

#include "SFML/Graphics.hpp"

class ComponentManager;
class Actor;


class World
{
public:
	~World();
	void InitializeWorld(ComponentManager* compManager);
	void Update();

private:
	void InitializeGround();
	void InitializeBackGround();
	void CreatePlatform(sf::Vector2f position, float length, float height = 1.0f);

private:
	ComponentManager* componentManager;
	std::vector<Actor*> worldObjects;
	std::vector<sf::Texture> Textures;

private:

	sf::Texture groundTileTexture;
	sf::Texture backgroundTexture;
	sf::Sprite* background;
	int platformIndex;
};

#endif // !WORLD_H