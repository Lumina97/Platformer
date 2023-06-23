#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H


enum ComponentFlags
{
	collision = 1,
	rendering = 2,
	animator = 4
};

inline ComponentFlags operator|(ComponentFlags a, ComponentFlags b)
{
	return static_cast<ComponentFlags>(static_cast<int>(a) | static_cast<int>(b));
}


#include "Component.h"
#include "Collider.h"
#include "CollisionDetection.h"
#include "ActorRenderer.h"
#include "Actor.h"
#include "SFML/Graphics.hpp"
#include <string>
#include "PlayerInput.h"
#include "Animator.h"

class ComponentManager
{

public:
	ComponentManager(sf::RenderWindow* renderWindow);

public:
	void SetPlayerInput(PlayerInput* input);


	template<typename T>
	T* CreateNewActor(sf::Vector2f position, sf::Vector2f size,
		std::string name, ComponentFlags componentFlags);


	template<typename T>
	T* CreateNewActor(sf::Vector2f position, sf::Vector2f size,
		std::string name);

	void UpdateComponents();


private:

	CollisionDetection* collisionDetection;
	PlayerInput* input;

	std::vector<Actor*> sceneActors;
	std::vector<Animator*> animators;
	std::vector<Component*> actorComponents;
	sf::RenderWindow* window;
};


template<typename T>
inline T* ComponentManager::CreateNewActor(sf::Vector2f position, sf::Vector2f size, std::string name, ComponentFlags componentFlags)
{
	T* newActor = CreateNewActor<T>(position, size, name);

	if (componentFlags & ComponentFlags::collision)
	{
		Physics::Collider* collider = new Physics::Collider(position, size, newActor);
		newActor->AddComponent(collider);
	
		actorComponents.push_back(collider);
		if(collisionDetection != nullptr)
			collisionDetection->AddCollider(collider);
	}

	if (componentFlags & ComponentFlags::rendering)
	{
		ActorRenderer* renderer = new ActorRenderer(size, window,newActor);
		newActor->AddComponent(renderer);
	
		actorComponents.push_back(renderer);
	}

	if (componentFlags & ComponentFlags::animator)
	{
		Animator* anim = new Animator(window, newActor);
		newActor->AddComponent(anim);

		animators.push_back(anim);
	}

	return newActor;
}

template<typename T>
inline T* ComponentManager::CreateNewActor(sf::Vector2f position, sf::Vector2f size, std::string name)
{
	T* newActor = new T(position, size, name);
	newActor->setPosition(position);
	sceneActors.push_back(newActor);
	return newActor;
}

#endif // !COMPONENT_MANAGER_H
