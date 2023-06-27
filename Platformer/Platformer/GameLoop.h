#ifndef  GAMELOOP_H
#define GAMELOOP_H

#include "Scene.h"
#include <vector>
#include "ComponentManager.h"

class GameLoop
{
public:
	void InitializeGameLoop(ComponentManager* componentManager);
	void RunUpdateLoop();

	static void ReloadCurrentSene();

	~GameLoop();

private:
	ComponentManager* compManager;	
	std::vector<Scene*> scenes;
	static Scene* CurrentScene;
};

#endif // ! GAMELOOP_H
