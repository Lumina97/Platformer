#include "GameGUI.h"
#include "Globals.h"
#include "Log.h"
#include "GameLoop.h"

GameGUI::GameGUI()
{
	gui = new tgui::Gui(*GLOBAL::WINDOW);
	GLOBAL::SetGUI(gui);
	try
	{
		gui->loadWidgetsFromFile("./Resources/GUI/GameGui.txt");
		GameElementsGrp = gui->get<tgui::Group>("GameElements");
		GameElementsGrp.get()->setSize(GLOBAL::ScreenSize.x, GLOBAL::ScreenSize.y);

		GameOverGrp = gui->get<tgui::Group>("GameOver");
		GameOverGrp.get()->setSize(GLOBAL::ScreenSize.x, GLOBAL::ScreenSize.y);
		SetGameOverScreen(false);

		HealthBar = gui->get<tgui::ProgressBar>("Health");
		HealthBar.get()->setPosition(GLOBAL::ScreenSize.x / 2 - HealthBar.get()->getSize().x / 2,
			GLOBAL::ScreenSize.y * 0.8f);

		gui->get<tgui::Label>("Label1")->setPosition(GLOBAL::ScreenSize.x / 2 - gui->get<tgui::Label>("Label1")->getSize().x / 2,
			GLOBAL::ScreenSize.y * 0.2f);

		b_exit = gui->get<tgui::Button>("B_Exit");
		b_exit.get()->onClick(GameGUI::ExitGame);
		b_exit.get()->setPosition(GLOBAL::ScreenSize.x / 2 - b_exit.get()->getSize().x / 2,
			GLOBAL::ScreenSize.y * 0.8f);

		b_restart = gui->get<tgui::Button>("B_Restart");
		b_restart.get()->onClick(GameLoop::ReloadCurrentSene);
		b_restart.get()->setPosition(GLOBAL::ScreenSize.x / 2 - b_restart.get()->getSize().x / 2,
			GLOBAL::ScreenSize.y * 0.9f);
	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "Failed to load GUI: " << e.what() << std::endl;
	}
}

void GameGUI::ChangeHealth(float newValue)
{
	if (HealthBar == nullptr)
	{
		LOG_WARN("Could not change health! Healthbar not set!");
		return;
	}

	HealthBar.get()->setValue(newValue);
}

void GameGUI::SetGameOverScreen(bool enabled)
{
	if (GameOverGrp == nullptr)
	{
		LOG_WARN("Could not enable game over screen.");
		return;
	}

	GameOverGrp.get()->setEnabled(enabled);
	GameOverGrp.get()->setVisible(enabled);

	SetGameElementsScreenVisible(!enabled);	
}

void GameGUI::SetGameElementsScreenVisible(bool visible)
{
	GameElementsGrp.get()->setEnabled(visible);
	GameElementsGrp.get()->setVisible(visible);
}



void GameGUI::ExitGame()
{
	if (GLOBAL::WINDOW) GLOBAL::WINDOW->close();
}
