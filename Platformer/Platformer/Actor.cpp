#include "Actor.h"
#include "Engine.h"
#include "Globals.h"
#include "ComponentManager.h"
#include "Component.h"
#include "Collider.h"

Actor::Actor(sf::Vector2f position, sf::Vector2f size, std::string name)
{
	setOrigin(size.x / 2, size.y);
	setPosition(position);

	this->size = size;
	this->name = name;
}

Actor::~Actor()
{
	for (int i = 0; i < components.size(); i++)
	{
		RemoveComponent(components[i]);
	}
	components.clear();
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
		int position = std::distance(components.begin(), id);

		ComponentManager::Destroy(components[position]);
	}
}

sf::Vector2f Actor::GetSize()
{
	return size;
}
