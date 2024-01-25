#include "EditorGUI.h"
#include "Globals.h"
#include <iostream>

using namespace tgui;

EditorGUI::EditorGUI(sf::RenderWindow* window)
{
	this->window = window;
	mainGUI.setWindow(*window);
}

void EditorGUI::RenderGUI()
{
	mainGUI.draw();
}
