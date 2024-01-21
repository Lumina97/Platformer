#include "Collider.h"
#include <iostream>
#include "Actor.h"
#include "Globals.h"
#include "Debug.h"
#include "CollisionDetection.h"

using namespace sf;


Physics::Collider::Collider(Vector2f position, Vector2f size,  Actor* parent)
{
	setOrigin(parent->getOrigin());
	setPosition(position);
	this->parentActor = parent;
	this->size = size;
	this->type = ComponentType::collider;
}

Physics::Collider::~Collider()
{
	CollisionDetection::RemoveCollider(this);
}

FloatRect Physics::Collider::GetBounds()
{
	if (parentActor == nullptr) return FloatRect(0,0,0,0);
	Vector2f topLeft = parentActor->getPosition();
	Vector2f origin = getOrigin();
	topLeft -= origin;

	FloatRect bounds(topLeft.x, topLeft.y, size.x, size.y);

	return bounds;
}

void Physics::Collider::UpdateComponent()
{
	Component::UpdateComponent(); 
	Debug::DrawDebugBox(getPosition(), getOrigin(), getRotation(), size,sf::Color::Transparent,sf::Color::Black,1.5f,1);
}
