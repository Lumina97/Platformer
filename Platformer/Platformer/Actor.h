#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include "SFML/Graphics.hpp"
#include "Collider.h"
#include <iostream>

class Actor : public sf::Transformable
{

public:
	Actor() {};
	Actor(sf::Vector2f position, sf::Vector2f size,std::string name);
	~Actor();

	virtual void OnCollision(Physics::CollisionDirection direction, float overlapAmount, Physics::Collider* other = nullptr) {};
	virtual void UpdateActor() {};
	virtual sf::FloatRect GetNextBounds() { return sf::FloatRect(getPosition() - getOrigin(), size); };

	template<typename T> 
	T* GetComponent();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	sf::Vector2f GetSize();

protected:
	sf::Vector2f size;
	std::string name;

	std::vector<Component*> components;
};

template<typename T>
inline T* Actor::GetComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		T* comp = dynamic_cast<T*>(components[i]);
		if (comp != nullptr)
		{
			return comp;
		}
	}

	return nullptr;
}


#endif // !ACTOR_H