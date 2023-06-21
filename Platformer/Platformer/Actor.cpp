#include "Actor.h"
#include "Engine.h"
#include "Globals.h"

Actor::Actor(sf::Vector2f position, sf::Vector2f size, std::string name)
{
	setOrigin(size.x / 2, size.y);
	setPosition(position);

	this->size = size;
	this->name = name;
}

void Actor::AddComponent(Component* component)
{
	components.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	std::_Vector_iterator id = std::find(components.begin(), components.end(), component);
	if (id != components.end())
	{
		components.erase(id);
	}
}