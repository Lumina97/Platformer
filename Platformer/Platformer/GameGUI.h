#pragma once
#include "TGUI/TGUI.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>

class GameGUI
{
public:
	GameGUI();
	tgui::Gui* GetGUI() { return gui; }
	void ChangeHealth(float newValue);
	void SetGameOverScreen(bool enabled);
	void SetGameElementsScreenVisible(bool visible);


private:
	static void ExitGame();
private:
	tgui::Gui* gui;
	tgui::ProgressBar::Ptr HealthBar;

	tgui::Button::Ptr b_restart;
	tgui::Button::Ptr b_exit;
	tgui::Group::Ptr GameOverGrp;
	tgui::Group::Ptr GameElementsGrp;
};