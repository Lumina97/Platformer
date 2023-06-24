#include "GameLoop.h"
#include <string>
#include "Player.h"
#include "ComponentManager.h"
#include "Globals.h"
#include "World.h"
#include "Animation.h"

void GameLoop::InitializeGameLoop(sf::RenderWindow* renderWindow, ComponentManager* componentManager, Physics::CollisionDetection* collisionDetection)
{
	this->window = renderWindow;

	mainGUI = new GUI(window);
	mainGUI->SetGameFinished(gameState::running);

	compManager = componentManager;
	this->collisionDetection = collisionDetection;
	InitializePlayer();
	input = new PlayerInput(player);
	compManager->SetPlayerInput(input);

	world = new World();
	world->InitializeWorld(compManager);

	idleTex->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Idle/Idle-Sheet.png");
	runTex->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Run/Run-Sheet.png");
	attackTex->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Attack-01/Attack-01-Sheet.png");
}

void GameLoop::RunUpdateLoop()
{
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

bool GameLoop::InitializePlayer()
{
	Animation* idle = new Animation("Idle", idleTex, sf::IntRect(0, 0, 64, 80), 4, 0, 4, 0, 0);
	Animation* run = new Animation("Run", runTex, sf::IntRect(0, 0, 80, 80), 8, 0, 8, 0, 0);
	Animation* attack1 = new Animation("Attack1", attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 0);
	Animation* attack2 = new Animation("Attack2", attackTex, sf::IntRect(0, 0, 96, 80), 4, 0, 4, 0, 4);
	

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
		anim->SwitchAnimation("Idle");
	}
	return false;
}
