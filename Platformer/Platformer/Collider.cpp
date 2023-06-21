#include "Collider.h"
#include <iostream>
#include "Actor.h"
#include "Globals.h"

using namespace sf;


Physics::Collider::Collider(Vector2f position, Vector2f size,  Actor* parent)
{
	setOrigin(parent->getOrigin());
	setPosition(position);
	this->parentActor = parent;
	this->size = size;
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