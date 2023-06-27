#include "MainMenuScene.h"
#include "Globals.h"
#include "GameLoop.h"

void MainMenuScene::InitializeScene(ComponentManager* compManager)
{
	gui = new tgui::Gui(*GLOBAL::WINDOW);
	GLOBAL::SetGUI(gui);
	try
	{
		gui->loadWidgetsFromFile("./Resources/GUI/MainMenu.txt");
		auto grp = gui->get<tgui::Group>("Grp_MainMenu");
		grp.get()->setSize(GLOBAL::ScreenSize.x, GLOBAL::ScreenSize.y);

		b_Exit = gui->get<tgui::Button>("B_Exit");
		b_Exit.get()->onClick(MainMenuScene::ExitGame);
		b_Exit.get()->setPosition(GLOBAL::ScreenSize.x / 2 - b_Exit.get()->getSize().x / 2,
			GLOBAL::ScreenSize.y * 0.6f);

		b_Play = gui->get<tgui::Button>("B_Play");
		b_Play.get()->onClick(&GameLoop::PlayGame);
		b_Play.get()->setPosition(GLOBAL::ScreenSize.x / 2 - b_Play.get()->getSize().x / 2,
			GLOBAL::ScreenSize.y * 0.4f);
	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "Failed to load GUI: " << e.what() << std::endl;
	}
}

void MainMenuScene::UnloadScene()
{

}

void MainMenuScene::UpdateScene()
{

}

void MainMenuScene::ReloadScene()
{

}

void MainMenuScene::ExitGame()
{
	if (GLOBAL::WINDOW) GLOBAL::WINDOW->close();
}
