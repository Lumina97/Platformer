#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "PlayerInput.h"

class World;
class Entity;
class ComponentManager;
class EnemyAI;

class GameScene :
	public Scene
{
public:
	~GameScene();

	// Inherited via Scene
	virtual void InitializeScene(ComponentManager* compManager) override;
	virtual void UnloadScene() override;
	virtual void UpdateScene() override;
	virtual void ReloadScene() override;

private:
	void InitializePlayer();
	void InitializeEnemy();

private:
	Entity* player;
	Entity* enemy;
	EnemyAI* ai;
	PlayerInput* input;
	ComponentManager* compManager;
	World* world;
	GameGUI* gui;
	bool isSceneLoaded;

	sf::Texture idleTex;
	sf::Texture runTex;
	sf::Texture attackTex;
	sf::Texture deathTex;


};
#endif // !GAMESCENE_H