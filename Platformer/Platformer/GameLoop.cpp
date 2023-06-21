#include "GameLoop.h"
#include <string>
#include "Player.h"
#include "ComponentManager.h"
#include "Globals.h"
#include "World.h"

void GameLoop::InitializeGameLoop(sf::RenderWindow* renderWindow, ComponentManager* componentManager)
{
	this->window = renderWindow;

	mainGUI = new GUI(window);
	mainGUI->SetGameFinished(gameState::running);

	compManager = componentManager;
	collisionDetection = new CollisionDetection();
	
	
	player = compManager->CreateNewActor<Player>(
			sf::Vector2f(GLOBAL::ScreenSize.x/2,GLOBAL::ScreenSize.y/2), sf::Vector2f(20, 60),
			std::string("Player"),ComponentFlags::collision | ComponentFlags::rendering);


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
