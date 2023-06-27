#include "GameLoop.h"
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "ComponentManager.h"
#include "Globals.h"
#include "World.h"
#include "Animation.h"

void GameLoop::InitializeGameLoop(sf::RenderWindow* renderWindow, ComponentManager* componentManager, Physics::CollisionDetection* collisionDetection)
{
	this->window = renderWindow;
	this->compManager = componentManager;
	this->collisionDetection = collisionDetection;

	mainGUI = new GUI(window);
	mainGUI->SetGameFinished(gameState::running);

	world = new World();
	world->InitializeWorld(compManager);
	InitializePlayer();
	InitializeEnemy();
	input = new PlayerInput(player);
	compManager->SetPlayerInput(input);

	idleTex->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Idle/Idle-Sheet.png");
	runTex->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Run/Run-Sheet.png");
	attackTex->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Attack-01/Attack-01-Sheet.png");
	deathTex->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Dead/Dead-Sheet.png");

}

void GameLoop::RunUpdateLoop()
{
	world->Update();
	compManager->UpdateComponents();
}

tgui::Gui* GameLoop::GetGUI()
{
	if (mainGUI != nullptr)
	{
		tgui::SFML_GRAPHICS::Gui* returnGui = mainGUI->GetGUI();
		if (returnGui != nullptr)
			return returnGui;
	}
	return nullptr;
}

void GameLoop::InitializePlayer()
{
	Animation* idle = new Animation("Idle", idleTex, sf::IntRect(0, 0, 64, 80), 4, 0, 4, 0, 0);
	Animation* run = new Animation("Run", runTex, sf::IntRect(0, 0, 80, 80), 8, 0, 8, 0, 0);
	Animation* attack1 = new Animation("Attack1", attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 0, false);
	Animation* attack2 = new Animation("Attack2", attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 4, false);
	Animation* death = new Animation("Death", deathTex, sf::IntRect(0, 0, 80, 60), 8, 0, 8, 0, 0, false);
	Animation* dead = new Animation("Dead", deathTex, sf::IntRect(0, 0, 80, 60), 1, 0, 1, 0,7, false);


	player = compManager->CreateNewActor<Player>(
		sf::Vector2f((float)(GLOBAL::ScreenSize.x / 2), (float)(GLOBAL::ScreenSize.y / 2)), sf::Vector2f(40, 100),
		std::string("Player"), ComponentType::collider | ComponentType::animator);

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

void GameLoop::InitializeEnemy()
{
	Animation* idle = new Animation("Idle", idleTex, sf::IntRect(0, 0, 64, 80), 4, 0, 4, 0, 0);
	Animation* run = new Animation("Run", runTex, sf::IntRect(0, 0, 80, 80), 8, 0, 8, 0, 0);
	Animation* attack1 = new Animation("Attack1", attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 0, false);
	Animation* attack2 = new Animation("Attack2", attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 4, false);
	Animation* death = new Animation("Death", deathTex, sf::IntRect(0, 0, 80, 80), 8, 0, 8, 0, 0, false);
	Animation* dead = new Animation("Dead", deathTex, sf::IntRect(0, 0, 80, 80), 1, 0, 1, 0, 7, false);

	enemy = compManager->CreateNewActor<Enemy>(
		sf::Vector2f((float)(200.0f), (float)(600.0f)), sf::Vector2f(40, 100),
		std::string("Enemy"), ComponentType::collider | ComponentType::animator);

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
