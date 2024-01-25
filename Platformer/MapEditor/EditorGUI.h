#ifndef EDITORGUI_H
#define EDITORGUI_H

#include "TGUI/TGUI.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "SFML/Graphics.hpp"

class EditorGUI
{
public:
	EditorGUI(sf::RenderWindow* window);
	void RenderGUI();
	tgui::Gui* GetGUI();



private:
	tgui::Gui mainGUI;
	sf::RenderWindow* window;

	tgui::Label::Ptr playerScoreText;
	tgui::Label::Ptr gameFinishedLabel;
};

inline tgui::Gui* EditorGUI::GetGUI() { return &mainGUI; }

#endif // !GUI_H
