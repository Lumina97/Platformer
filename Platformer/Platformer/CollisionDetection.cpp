#include "CollisionDetection.h"
#include "Engine.h"
#include "Globals.h"
#include "Math.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Actor.h"

namespace Physics
{
	std::vector<Physics::Collider*> CollisionDetection::colliders;

	sf::FloatRect CollisionDetection::WillCollideInDirection(Physics::Collider* collider)
	{
		sf::FloatRect collisionRect(-1, -1, -1, -1);
		for (int i = 0; i < colliders.size(); i++)
		{
			if (CheckCollisions(collider, colliders[i]))
				collisionRect = colliders[i]->GetBounds();
		}
		return collisionRect;
	}

	void CollisionDetection::UpdateCollision()
	{
		if (colliders.size() == 0) return;

		for (int c = 0; c < colliders.size(); c++)
		{
			if (colliders[c] != nullptr && colliders[c]->GetHasMoved())
			{
				for (int i = 0; i < colliders.size(); i++)
				{
					if (CheckCollisions(colliders[c], colliders[i]))
						ResolveCollision(colliders[c], colliders[i]);
				}
			}
		}
	}

	void CollisionDetection::AddCollider(Physics::Collider* collider)
	{
		std::_Vector_iterator id = std::find(colliders.begin(), colliders.end(), collider);
		if (id == colliders.end())
		{
			colliders.push_back(collider);
		}
	}

	void CollisionDetection::RemoveCollider(Physics::Collider* collider)
	{
		std::_Vector_iterator id = std::find(colliders.begin(), colliders.end(), collider);
		if (id != colliders.end())
		{
			colliders.erase(id);
		}
	}

	Physics::CollisionDirection CollisionDetection::GetOverlapAmount(const sf::FloatRect& collider, const sf::FloatRect& other, float& overlap)
	{
		// Calculate the overlap between the player and obstacle
		float xOverlap = std::min(collider.left + collider.width, other.left + other.width) -
			std::max(collider.left, other.left);

		float yOverlap = std::min(collider.top + collider.height, other.top + other.height) -
			std::max(collider.top, other.top);


		// Determine the smallest axis of overlap
		if (xOverlap < yOverlap)
		{
			// Adjust player's position horizontally
			if (collider.left < other.left) {
				overlap = xOverlap;
				return Physics::CollisionDirection::right;
			}
			else {
				overlap = xOverlap;
				return Physics::CollisionDirection::left;
			}
		}
		else {
			// Adjust player's position vertically
			if (collider.top < other.top)
			{
				overlap = yOverlap;
				return Physics::CollisionDirection::top;
			}
			else
			{
				overlap = yOverlap;
				return Physics::CollisionDirection::bottom;
			}
		}

		return Physics::CollisionDirection::none;
	}

	void CollisionDetection::ResolveCollision(Physics::Collider* collider, Physics::Collider* other)
	{
		Actor* actor = collider->GetParentActor();
		sf::FloatRect colliderBounds = collider->GetBounds();
		sf::FloatRect otherBounds = other->GetBounds();


		// Calculate the overlap between the player and obstacle
		float xOverlap = std::min(colliderBounds.left + colliderBounds.width, otherBounds.left + otherBounds.width) -
			std::max(colliderBounds.left, otherBounds.left);

		float yOverlap = std::min(colliderBounds.top + colliderBounds.height, otherBounds.top + otherBounds.height) -
			std::max(colliderBounds.top, otherBounds.top);


		// Determine the smallest axis of overlap
		if (xOverlap < yOverlap)
		{
			// Adjust player's position horizontally
			if (colliderBounds.left < otherBounds.left) {
				actor->OnCollision(Physics::CollisionDirection::right, xOverlap, other);
				return;
			}
			else {
				actor->OnCollision(Physics::CollisionDirection::left, xOverlap, other);
				return;
			}
		}
		else {
			// Adjust player's position vertically
			if (colliderBounds.top < otherBounds.top)
			{
				actor->OnCollision(Physics::CollisionDirection::top, yOverlap, other);
				return;
			}
			else
			{
				actor->OnCollision(Physics::CollisionDirection::bottom, yOverlap, other);
				return;
			}
		}
	}

	bool CollisionDetection::CheckCollisions(Physics::Collider* collider, Physics::Collider* other)
	{
		//checking for self collision
		if (collider == other)
		{
			return false;
		}

		if (collider == nullptr || other == nullptr) return false;

		Actor* actor = collider->GetParentActor();
		sf::FloatRect colliderBounds;
		if (actor != nullptr)
			colliderBounds = actor->GetNextBounds();
		else
			colliderBounds = collider->GetBounds();

		sf::FloatRect otherBounds = other->GetBounds();


		//	line 1 — A’s top is above B’s bottom.
		//	line 2 — A’s bottom is lower than B’s top.
		//	line 3 — A’s left side is to the left of B’s right side.
		//	line 4 — A’s right side is to the right of B’s left side.

		if (colliderBounds.top < otherBounds.top + otherBounds.height &&
			colliderBounds.top + colliderBounds.height > otherBounds.top &&
			colliderBounds.left < otherBounds.left + otherBounds.width &&
			colliderBounds.left + colliderBounds.width  > otherBounds.left)
		{
			return true;
		}
		return false;
	}

	bool CollisionDetection::CheckCollisions(sf::FloatRect testBounds, Collider* other)
	{
		sf::FloatRect otherBounds = other->GetBounds();
		if (testBounds.top < otherBounds.top + otherBounds.height &&
			testBounds.top + testBounds.height > otherBounds.top &&
			testBounds.left < otherBounds.left + otherBounds.width &&
			testBounds.left + testBounds.width  > otherBounds.left)
		{
			return true;
		}
		return false;
	}


	std::vector<Collider*> CollisionDetection::BoxCastAll(sf::Vector2f position, float rotation, sf::Vector2f size)
	{
		sf::FloatRect testCollision;
		testCollision.width = size.x;
		testCollision.height = size.y;
		testCollision.left = position.x - size.x / 2;
		testCollision.top = position.y - size.y / 2;

		std::vector<Collider*> collisions;

		for (int c = 0; c < colliders.size(); c++)
		{
			for (int i = 0; i < colliders.size(); i++)
			{
				if (i == c) continue;

				if (testCollision.intersects(colliders[i]->GetBounds()))
				{
					if (collisions.size() > 0)
					{
						std::_Vector_iterator id  = std::find(collisions.begin(), collisions.end(), colliders[i]);
						if (id == collisions.end())
							collisions.push_back(colliders[i]);
					}
					else
						collisions.push_back(colliders[i]);
				}
			}
		}
		return collisions;
	}

	Collider* CollisionDetection::BoxCast(sf::Vector2f position, float rotation, sf::Vector2f size)
	{
		sf::FloatRect testCollision;
		testCollision.width = size.x;
		testCollision.height = size.y;
		testCollision.left = position.x - size.x / 2;
		testCollision.top = position.y - size.y / 2;

		std::vector<Collider*> collisions;

		for (int c = 0; c < colliders.size(); c++)
		{
			for (int i = 0; i < colliders.size(); i++)
			{
				if (i == c) continue;

				if (testCollision.intersects(colliders[i]->GetBounds()))
				{
					return colliders[i];
					
				}
			}
		}
		return nullptr;
	}
}