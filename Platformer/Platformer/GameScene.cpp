#include "GameScene.h"
#include <string>
#include "Entity.h"
#include "ComponentManager.h"
#include "Globals.h"
#include "World.h"
#include "Animator.h"
#include "GameGUI.h"
#include "EnemyAI.h"

void GameScene::InitializeScene(ComponentManager* compManager)
{
	this->compManager = compManager;

	idleTex.loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Idle/Idle-Sheet.png");
	runTex.loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Run/Run-Sheet.png");
	attackTex.loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Attack-01/Attack-01-Sheet.png");
	deathTex.loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Dead/Dead-Sheet.png");

	world = new World();
	world->InitializeWorld(compManager);
	InitializePlayer();
	InitializeEnemy();
	input = new PlayerInput(player);
	compManager->SetPlayerInput(input);
	isSceneLoaded = true;
}

void GameScene::UnloadScene()
{
	isSceneLoaded = false;
	ComponentManager::Destroy(player);
	ComponentManager::Destroy(enemy);
	delete(world);
	delete(input);
	delete(ai);
}

void GameScene::UpdateScene()
{
	if (isSceneLoaded == false) return;

	world->Update();
	compManager->UpdateComponents();
	ai->Update();
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
	Animation* idle = new Animation("Idle", &idleTex, sf::IntRect(0, 0, 64, 80), 4, 0, 4, 0, 0);
	Animation* run = new Animation("Run", &runTex, sf::IntRect(0, 0, 80, 80), 8, 0, 8, 0, 0);
	Animation* attack1 = new Animation("Attack1", &attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 0, false);
	Animation* attack2 = new Animation("Attack2", &attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 4, false);
	Animation* death = new Animation("Death", &deathTex, sf::IntRect(0, 0, 80, 60), 8, 0, 8, 0, 0, false);
	Animation* dead = new Animation("Dead", &deathTex, sf::IntRect(0, 0, 80, 60), 1, 0, 1, 0, 7, false);

	player = compManager->CreateNewActor<Entity>(
		sf::Vector2f((float)(GLOBAL::ScreenSize.x / 2), (float)(GLOBAL::ScreenSize.y / 2 + 200.0f)), sf::Vector2f(40, 100),
		std::string("Player"), ComponentType::collider | ComponentType::animator);

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