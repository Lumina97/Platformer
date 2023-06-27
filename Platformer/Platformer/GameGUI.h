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
	void SetScore(const char* value);


private:
	static void ExitGame();
private:
	tgui::Gui* gui;
	tgui::Label::Ptr scoreLabel;
	tgui::ProgressBar::Ptr HealthBar;

	tgui::Button::Ptr b_restart;
	tgui::Button::Ptr b_exit;
	tgui::Group::Ptr GameOverGrp;
	tgui::Group::Ptr GameElementsGrp;
};