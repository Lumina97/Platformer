#include "Debug.h"
namespace Debug
{
	void DrawDebugBox(sf::RectangleShape* shape)
	{
		if (GLOBAL::WINDOW == nullptr) return;

		GLOBAL::WINDOW->draw(*shape);

	}

	void DrawDebugBox(sf::Vector2f position, sf::Vector2f origin, float rotationAngle, sf::Vector2f size)
	{
		if (GLOBAL::WINDOW == nullptr) return;

		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(size));
		shape.setOrigin(origin);
		shape.setPosition(position);
		shape.setRotation(rotationAngle);

		GLOBAL::WINDOW->draw(shape);
	}

	void DrawDebugBox(sf::Vector2f position, sf::Vector2f origin, float rotationAngle, sf::Vector2f size,
		sf::Color fillColor = sf::Color::Transparent, sf::Color outlineColor = sf::Color::White,
		float outlineThickness = 0, float scale = 0)
	{
		if (GLOBAL::WINDOW == nullptr) return;

		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(size));
		shape.setOrigin(origin);
		shape.setPosition(position);
		shape.setRotation(rotationAngle);
		shape.setScale(scale, scale);
		shape.setFillColor(fillColor);
		shape.setOutlineColor(outlineColor);
		shape.setOutlineThickness(outlineThickness);



		GLOBAL::WINDOW->draw(shape);
	}
}