#ifndef WORLD_H
#define WORLD_H

#include "ComponentManager.h"
#include "Actor.h"

class World
{
public:

	void InitializeWorld(ComponentManager* compManager);


private:
	ComponentManager* componentManager;
	std::vector<Actor*> worldObjects;

};

#endif // !WORLD_H