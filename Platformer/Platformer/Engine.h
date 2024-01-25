#ifndef ENGINE_H
#define ENGINE_H


#include "SFML/Graphics.hpp"

class SoundEngine;
class GameLoop;
class ComponentManager;

namespace Physics {
	class CollisionDetection;
}

using namespace sf;


class Engine
{
public:
	bool Init();
	void Run();	

	


private:
	VideoMode videoMode;
	RenderWindow window;
	sf::View Camera;
	ComponentManager* compManager;
	Physics::CollisionDetection* collisionDetection;
	SoundEngine* soundEngine;
	GameLoop* gameLoop;	
};

#endif // ! ENGINE_H
