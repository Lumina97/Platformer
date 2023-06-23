#include "GameLoop.h"
#include <string>
#include "Player.h"
#include "ComponentManager.h"
#include "Globals.h"
#include "World.h"
#include "Animation.h"

void GameLoop::InitializeGameLoop(sf::RenderWindow* renderWindow, ComponentManager* componentManager)
{
	this->window = renderWindow;

	mainGUI = new GUI(window);
	mainGUI->SetGameFinished(gameState::running);

	compManager = componentManager;
	collisionDetection = new CollisionDetection();

	InitializePlayer();
	
	Actor* actor = compManager->CreateNewActor<Actor>(
		sf::Vector2f(GLOBAL::ScreenSize.x / 2 + 100 , GLOBAL::ScreenSize.y / 2 + 100), sf::Vector2f(100, 300),
		std::string("Dummy"), ComponentFlags::collision | ComponentFlags::rendering);

	input = new PlayerInput(player);
	compManager->SetPlayerInput(input);

	world = new World();
	world->InitializeWorld(compManager);
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
	sf::Texture* idleTex = new sf::Texture();
	idleTex->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Idle/Idle-Sheet.png");
	Animation* idle = new Animation("Idle", idleTex, sf::IntRect(0, 0, 64, 80), 4, 0, 4, 0, 0);
	Textures.push_back(*idleTex);


	sf::Texture* runTex = new sf::Texture();
	runTex->loadFromFile("./Resources/Legacy-Fantasy - High Forest 2.3/Character/Run/Run-Sheet.png");
	Animation* run = new Animation("Run", runTex, sf::IntRect(0, 0, 80, 80), 8, 0, 8, 0, 0);
	Textures.push_back(*runTex);


	player = compManager->CreateNewActor<Player>(
		sf::Vector2f((float)(GLOBAL::ScreenSize.x / 2), (float)(GLOBAL::ScreenSize.y / 2)), sf::Vector2f(20, 60),
		std::string("Player"), ComponentFlags::collision | ComponentFlags::animator); // ComponentFlags::rendering |

	Animator* anim = player->GetComponent<Animator>();
	if (anim)
	{
		anim->AddAnimation(idle);
		anim->AddAnimation(run);
		anim->SwitchAnimation("Idle");
	}
	return false;
}
