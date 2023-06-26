#ifndef  DEBUG
#define DEBUG

#include "Globals.h"
#include "SFML/Graphics.hpp"


namespace Debug
{
	struct DebugShape
	{
		sf::Shape& shapeToDraw;
		float timeToDisplay;
		float startTime;
		float endtime;
		DebugShape()  = default;
		DebugShape(sf::Shape& n, float ttd, float st, float et)
			: shapeToDraw(n), timeToDisplay(ttd), startTime(st), endtime(et) { }
	};

	void DrawDebugBox(sf::RectangleShape* shape);
	void DrawDebugBox(sf::Vector2f position, sf::Vector2f origin, float rotationAngle, sf::Vector2f size);
	void DrawDebugBox(sf::Vector2f position, sf::Vector2f origin, float rotationAngle, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, float outlineThickness, float scale);
	void DrawDebugBox(sf::Vector2f position, sf::Vector2f origin, float rotationAngle, sf::Vector2f size, float time, sf::Color fillColor,sf::Color outlineColor, float outlineThickness , float scale );
	void Update();


	static std::vector<DebugShape*> debugShapes;
}
#endif // ! DEBUG