#ifndef ENGINE_H
#define ENGINE_H


#include "SFML/Graphics.hpp"
#include "SoundEngine.h"
#include "GameLoop.h"
#include "ComponentManager.h"

using namespace sf;


class Engine
{
public:
	bool Init();
	void Run();	

	


private:
	VideoMode videoMode;
	RenderWindow window;

	ComponentManager* compManager;
	Physics::CollisionDetection* collisionDetection;
	SoundEngine* soundEngine;
	GameLoop* gameLoop;	
};

#endif // ! ENGINE_H
