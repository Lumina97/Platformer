#ifndef COLLIDER_H
#define COLLIDER_H

#include "SFML/Graphics.hpp"
#include "Component.h"

namespace Physics
{
	///Which way the tested collider is colliding
	///if player is tested and colliding with floor
	/// == bottom
	enum CollisionDirection {
		none = 0,
		top = 1,
		bottom = 2,
		left = 4,
		right = 8
	};
	inline CollisionDirection operator|(CollisionDirection a, CollisionDirection b)
	{
		return static_cast<CollisionDirection>(static_cast<int>(a) | static_cast<int>(b));
	}

	class Collider : public Component
	{

	public:
		Collider(sf::Vector2f position, sf::Vector2f size, Actor* parent);
		sf::FloatRect GetBounds();


	private:
		sf::Vector2f size;
		sf::RenderWindow* window = nullptr;

	};
}
#endif // !COLLIDER_H