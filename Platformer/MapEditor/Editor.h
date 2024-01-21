#pragma once

#include "SFML/Graphics.hpp"

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
};