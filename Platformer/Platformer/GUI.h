
#ifndef GUI_H
#define GUI_H

#include "TGUI/TGUI.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "SFML/Graphics.hpp"

enum gameState
{
	player,
	enemy,
	running
};


class GUI
{
public:
	GUI(sf::RenderWindow* window);
	void RenderGUI();
	tgui::Gui* GetGUI();
	void SetScore(int player, int enemy);
	void SetGameFinished(gameState winstate);

private:
	void InitializePlayerScoreLabel();
	void InitializeFinishedGameLabel();



private:
	tgui::Gui mainGUI;
	sf::RenderWindow* window;

	tgui::Label::Ptr playerScoreText;
	tgui::Label::Ptr gameFinishedLabel;
};

inline tgui::Gui* GUI::GetGUI() { return &mainGUI; }

#endif // !GUI_H
