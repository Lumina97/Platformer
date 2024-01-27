#include "GameScene.h"
#include <string>
#include "Entity.h"
#include "ComponentManager.h"
#include "Globals.h"
#include "World.h"
#include "Animator.h"
#include "Animation.h"
#include "GameGUI.h"
#include "EnemyAI.h"
#include "PlayerInput.h"
#include "Log.h"
#include "Player.h"

void GameScene::InitializeScene(ComponentManager* compManager)
{
	this->compManager = compManager;

	idleTex.loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Idle/Idle-Sheet.png");
	runTex.loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Run/Run-Sheet.png");
	attackTex.loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Attack-01/Attack-01-Sheet.png");
	deathTex.loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Dead/Dead-Sheet.png");

	idle = new Animation("Idle", &idleTex, sf::IntRect(0, 0, 64, 80), 4, 0, 4, 0, 0);
	run = new Animation("Run", &runTex, sf::IntRect(0, 0, 80, 80), 8, 0, 8, 0, 0);
	attack1 = new Animation("Attack1", &attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 0, false);
	attack2 = new Animation("Attack2", &attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 4, false);
	death = new Animation("Death", &deathTex, sf::IntRect(0, 0, 80, 60), 8, 0, 8, 0, 0, false);
	dead = new Animation("Dead", &deathTex, sf::IntRect(0, 0, 80, 60), 1, 0, 1, 0, 7, false);

	player = compManager->CreateNewActor<Player>(
		sf::Vector2f(0, 200.0f), sf::Vector2f(16, 32),
		std::string("Player"), ComponentType::collider | ComponentType::animator);
	InitializePlayer();
	input = new PlayerInput(player);
	compManager->SetPlayerInput(input);

	try
	{
		map.load("assets/Scene_Gameplay.tmx");

		const auto& layers = map.getLayers();

		for (int i = 0; i < layers.size(); i++)
		{
			if (layers[i]->getType() != tmx::Layer::Type::Object)
				mapLayers.push_back(new MapLayer(map, i));
		}

		for (const auto& layer : layers)
		{
			if (layer->getType() == tmx::Layer::Type::Object)
			{
				const auto& objects = layer->getLayerAs<tmx::ObjectGroup>().getObjects();
				for (const auto& object : objects)
				{
					sf::Vector2f position(object.getPosition().x, object.getPosition().y);
					sf::Vector2f size(object.getAABB().width, object.getAABB().height);
					Actor* actor = compManager->CreateNewActor<Actor>(position, size, object.getName(), ComponentType::collider);
				}
			}
		}
	}
	catch (const std::exception&)
	{
		ENGINE_LOG_ERROR("There was an error loading the map! TestScene!");
	}
	isSceneLoaded = true;
}

void GameScene::UnloadScene()
{
	isSceneLoaded = false;
	ComponentManager::Destroy((Actor*)player);
	ComponentManager::Destroy(enemy);
	delete(world);
	delete(input);
	delete(ai);
}

void GameScene::UpdateScene()
{
	if (isSceneLoaded == false) return;

	for (auto a : mapLayers)
	{
		GLOBAL::WINDOW->draw(*a);
	}
	compManager->UpdateComponents();

	if (ai != nullptr) ai->Update();
}

void GameScene::ReloadScene()
{
	UnloadScene();
	InitializeScene(compManager);
	if (gui) gui->SetGameOverScreen(false);
	if (gui) gui->SetGameElementsScreenVisible(true);
}

GameScene::~GameScene()
{
	UnloadScene();
}

void GameScene::InitializePlayer()
{
	if (gui == nullptr)
		gui = new GameGUI();

	player->SetGUI(gui);

	Animator* anim = player->GetComponent<Animator>();
	if (anim)
	{
		anim->AddAnimation(idle);
		anim->AddAnimation(run);
		anim->AddAnimation(attack1);
		anim->AddAnimation(attack2);
		anim->AddAnimation(death);
		anim->AddAnimation(dead);
		anim->SwitchAnimation("Idle");
	}
}

void GameScene::InitializeEnemy()
{
	Animation* idle = new Animation("Idle", &idleTex, sf::IntRect(0, 0, 64, 80), 4, 0, 4, 0, 0);
	Animation* run = new Animation("Run", &runTex, sf::IntRect(0, 0, 80, 80), 8, 0, 8, 0, 0);
	Animation* attack1 = new Animation("Attack1", &attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 0, false);
	Animation* attack2 = new Animation("Attack2", &attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 4, false);
	Animation* death = new Animation("Death", &deathTex, sf::IntRect(0, 0, 80, 80), 8, 0, 8, 0, 0, false);
	Animation* dead = new Animation("Dead", &deathTex, sf::IntRect(0, 0, 80, 80), 1, 0, 1, 0, 7, false);

	enemy = compManager->CreateNewActor<Entity>(
		sf::Vector2f((float)(200.0f), (float)(600.0f)), sf::Vector2f(40, 100),
		std::string("Enemy"), ComponentType::collider | ComponentType::animator);
	ai = new EnemyAI(enemy, player);
	Animator* anim = enemy->GetComponent<Animator>();
	if (anim)
	{
		anim->AddAnimation(idle);
		anim->AddAnimation(run);
		anim->AddAnimation(attack1);
		anim->AddAnimation(attack2);
		anim->AddAnimation(death);
		anim->AddAnimation(dead);
		anim->SwitchAnimation("Idle");
	}
}