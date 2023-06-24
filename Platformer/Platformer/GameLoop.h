#ifndef  GAMELOOP_H
#define GAMELOOP_H

#include "GUI.h"
#include "CollisionDetection.h"
#include "SFML/Graphics.hpp"
#include "PlayerInput.h"

class World;
class Player;
class ComponentManager;

class GameLoop
{
public:
	void InitializeGameLoop(sf::RenderWindow* renderWindow, ComponentManager* componentManager, Physics::CollisionDetection* collisionDetection);
	void RunUpdateLoop();


	tgui::Gui* GetGUI();
private:

	bool InitializePlayer();

private:
	Player* player;
	PlayerInput* input;
	Physics::CollisionDetection* collisionDetection;
	ComponentManager* compManager;
	GUI* mainGUI;
	World* world;

	sf::Texture* idleTex = new sf::Texture();
	sf::Texture* runTex = new sf::Texture();
	sf::Texture* attackTex = new sf::Texture();

	sf::RenderWindow* window;
	std::vector<sf::Texture> Textures;
};

#endif // ! GAMELOOP_H
