#include "GameLoop.h"
#include "GameScene.h"

Scene* GameLoop::CurrentScene = nullptr;


void GameLoop::InitializeGameLoop(ComponentManager* componentManager)
{
	this->compManager = componentManager;
	GameScene* gameScene = new GameScene();
	gameScene->InitializeScene(componentManager);
	scenes.push_back(gameScene);
	CurrentScene = gameScene;
}

void GameLoop::RunUpdateLoop()
{
	CurrentScene->UpdateScene();
}

void GameLoop::ReloadCurrentSene()
{
	CurrentScene->ReloadScene();
}

GameLoop::~GameLoop()
{
	for (int i = 0; i < scenes.size(); i++)
	{
		delete(scenes[i]);
	}
	scenes.clear();
}