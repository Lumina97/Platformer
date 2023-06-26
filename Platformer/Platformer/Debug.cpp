#include "Debug.h"
#include "Log.h"

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
		shape.setSize(size);
		shape.setOrigin(origin);
		shape.setPosition(position);
		shape.setRotation(rotationAngle);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(1.0f);
		GLOBAL::WINDOW->draw(shape);
	}

	void DrawDebugBox(sf::Vector2f position, sf::Vector2f origin, float rotationAngle, sf::Vector2f size,
		sf::Color fillColor = sf::Color::Transparent,
		sf::Color outlineColor = sf::Color::White,
		float outlineThickness = 0,
		float scale = 0)
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

	void DrawDebugBox(sf::Vector2f position, sf::Vector2f origin, float rotationAngle, sf::Vector2f size,
		float time = 0,
		sf::Color fillColor = sf::Color::Transparent,
		sf::Color outlineColor = sf::Color::White,
		float outlineThickness = 0,
		float scale = 0)
	{
		if (GLOBAL::WINDOW == nullptr) return;

		sf::RectangleShape* shape = new sf::RectangleShape();
		shape->setSize(sf::Vector2f(size));
		shape->setOrigin(origin);
		shape->setPosition(position);
		shape->setRotation(rotationAngle);
		shape->setScale(scale, scale);
		shape->setFillColor(fillColor);
		shape->setOutlineColor(outlineColor);
		shape->setOutlineThickness(outlineThickness);

		DebugShape* debugshape = new DebugShape(*shape,time,TIME::currentTime,time + TIME::currentTime);
		debugShapes.push_back(debugshape);

		GLOBAL::WINDOW->draw(*shape);
	}


	void Update()
	{
		for (int i = 0; i < debugShapes.size(); i++)
		{
			if (TIME::currentTime < debugShapes[i]->endtime)
				GLOBAL::WINDOW->draw(debugShapes[i]->shapeToDraw);
			else
			{
				//this will skip some of the entries during the loop
				//TODO: find a better way to delete objects out of the list and not skip a element in the list
				auto index = std::find(debugShapes.begin(), debugShapes.end(), debugShapes[i]);
				delete(&debugShapes[i]->shapeToDraw);
				delete(debugShapes[i]);
				debugShapes.erase(index);
				continue;
			}
		}
	}
}