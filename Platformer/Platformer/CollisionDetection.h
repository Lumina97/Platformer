#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <vector>
#include "Collider.h"


class CollisionDetection
{
public:
	void UpdateCollision();

	void AddCollider(Physics::Collider* collider);
	void RemoveCollider(Physics::Collider* collider);

	static bool IsColliding(Physics::Collider* collider);


private:

	static void ResolveCollision(Physics::Collider* collider, Physics::Collider* other);
	static bool CheckCollisions(Physics::Collider* collider, Physics::Collider* other);


private:
	static std::vector<Physics::Collider*> colliders;


};
#endif // !COLLISIONDETECTION_H



