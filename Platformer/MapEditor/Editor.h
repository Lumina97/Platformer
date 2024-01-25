#pragma once

#include "SFML/Graphics.hpp"
#include "EditorGUI.h"

using namespace sf;

class Editor
{
public:
	bool Init();
	void Run();


private:
	VideoMode videoMode;
	RenderWindow window;
	sf::View Camera;
	EditorGUI* Gui;
};