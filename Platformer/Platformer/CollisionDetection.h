#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#pragma once

#include <vector>
#include "SFML/graphics.hpp"



namespace Physics
{
	class Collider;
	enum  CollisionDirection : char;

	class CollisionDetection
	{
	public:
		void UpdateCollision();

		void AddCollider(Collider* collider);
		static void RemoveCollider(Collider* collider);

		static std::vector<sf::FloatRect> WillCollideInDirection(Collider* collider);
		static Physics::CollisionDirection GetOverlapAmount(const sf::FloatRect& collider, const sf::FloatRect& other, float& overlap);
		static Physics::CollisionDirection GetOverlapAmount(const sf::FloatRect& collider, const sf::FloatRect& other);
		static std::vector<Collider*> BoxCastAll(sf::Vector2f position, float rotation, sf::Vector2f size);
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



