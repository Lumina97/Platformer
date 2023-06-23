#ifndef  DEBUG
#define DEBUG

#include "Globals.h"
#include "SFML/Graphics.hpp"

namespace Debug
{
	void DrawDebugBox(sf::RectangleShape* shape);
	void DrawDebugBox(sf::Vector2f position, sf::Vector2f origin, float rotationAngle, sf::Vector2f size);
	void DrawDebugBox(sf::Vector2f position, sf::Vector2f origin, float rotationAngle, sf::Vector2f size, sf::Color fillColor = sf::Color::Transparent,sf::Color outlineColor = sf::Color::White, float outlineThickness = 0, float scale = 0);
}
#endif // ! DEBUG