#include "GameLoop.h"
#include "GameScene.h"
#include "MainMenuScene.h"

Scene* GameLoop::CurrentScene = nullptr;
ComponentManager* GameLoop::compManager = nullptr;
std::vector<Scene*> GameLoop::scenes;

void GameLoop::InitializeGameLoop(ComponentManager* componentManager)
{
	this->compManager = componentManager;
	GameScene* gameScene = new GameScene();	
	scenes.push_back(gameScene);
	MainMenuScene* mainMenu = new MainMenuScene();
	mainMenu->InitializeScene(compManager);
	scenes.push_back(mainMenu);
	CurrentScene = mainMenu;
}

void GameLoop::RunUpdateLoop()
{
	CurrentScene->UpdateScene();
}

void GameLoop::PlayGame()
{
	auto lastScene = CurrentScene;
	if (scenes.size() > 1)
	{
		CurrentScene = scenes[0];
		CurrentScene->InitializeScene(compManager);
	}
	lastScene->UnloadScene();

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