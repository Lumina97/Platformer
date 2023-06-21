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
	void InitializeGameLoop(sf::RenderWindow* renderWindow, ComponentManager* componentManager);
	void RunUpdateLoop();


	tgui::Gui* GetGUI();

private:
	Player* player;
	PlayerInput* input;
	CollisionDetection* collisionDetection;
	ComponentManager* compManager;
	GUI* mainGUI;
	World* world;

	sf::RenderWindow* window;

};

#endif // ! GAMELOOP_H
