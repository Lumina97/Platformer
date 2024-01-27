#ifndef GAMESCENE_H
#define GAMESCENE_H

#pragma once;

#include "Scene.h"
#include "SFML/Graphics.hpp"
#include "tmxlite/Map.hpp"
#include "MapLayer.h"

class World;
class Player;
class Entity;
class ComponentManager;
class EnemyAI;
class PlayerInput;
class GameGUI;
class Animation;

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
	Player* player;
	Entity* enemy;
	EnemyAI* ai;
	PlayerInput* input;
	ComponentManager* compManager;
	World* world;
	GameGUI* gui;
	bool isSceneLoaded;
	tmx::Map map;
	std::vector<MapLayer*> mapLayers;

	sf::Texture idleTex;
	sf::Texture runTex;
	sf::Texture attackTex;
	sf::Texture deathTex;

	Animation* idle;
	Animation* run;
	Animation* attack1;
	Animation* attack2;
	Animation* death;
	Animation* dead;
};
#endif // !GAMESCENE_H