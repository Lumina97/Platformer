#ifndef GAMESCENE_H
#define GAMESCENE_H

#pragma once;

#include "Scene.h"
#include "SFML/Graphics.hpp"

class World;
class Entity;
class ComponentManager;
class EnemyAI;
class PlayerInput;
class GameGUI;

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