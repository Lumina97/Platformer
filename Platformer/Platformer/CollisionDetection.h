#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <vector>
#include "Collider.h"
#include "SFML/graphics.hpp"
namespace Physics
{
	class CollisionDetection
	{
	public:
		void UpdateCollision();

		void AddCollider(Collider* collider);
		static void RemoveCollider(Collider* collider);

		static sf::FloatRect WillCollideInDirection(Collider* collider);
		static Physics::CollisionDirection GetOverlapAmount(const sf::FloatRect& collider, const sf::FloatRect& other, float& overlap);
		static Collider* BoxCast(sf::Vector2f position, float rotation, sf::Vector2f size);


	private:
		static void ResolveCollision(Collider* collider, Collider* other);
		static bool CheckCollisions(Collider* collider, Collider* other);
		static bool CheckCollisions(sf::FloatRect testBounds, Collider* other);


	private:
		static std::vector<Physics::Collider*> colliders;


	};
}

#endif // !COLLISIONDETECTION_H



