#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "Component.h"
#include "CollisionDetection.h"
#include "Actor.h"
#include "SFML/Graphics.hpp"
#include <string>
#include "PlayerInput.h"
#include "Animator.h"
#include "ActorRenderer.h"
#include "Collider.h"

class ComponentManager
{

public:
	ComponentManager(sf::RenderWindow* renderWindow, CollisionDetection* collisionDetection);

public:
	void SetPlayerInput(PlayerInput* input);


	template<typename T>
	T* CreateNewActor(sf::Vector2f position, sf::Vector2f size,
		std::string name, ComponentType ComponentTypes);


	template<typename T>
	T* CreateNewActor(sf::Vector2f position, sf::Vector2f size,
		std::string name);

	void UpdateComponents();

	static void Destroy(Actor* actor);
	static void Destroy(Component* Component);


private:

	CollisionDetection* collisionDetection;
	PlayerInput* input;

	static std::vector<Actor*> sceneActors;
	static std::vector<Animator*> animators;
	static std::vector<Component*> actorComponents;
	sf::RenderWindow* window;
};


template<typename T>
inline T* ComponentManager::CreateNewActor(sf::Vector2f position, sf::Vector2f size, std::string name, ComponentType ComponentTypes)
{
	T* newActor = CreateNewActor<T>(position, size, name);

	if (ComponentTypes & ComponentType::collider)
	{
		Physics::Collider* collider = new Physics::Collider(position, size, newActor);
		newActor->AddComponent(collider);
	
		actorComponents.push_back(collider);
		if(collisionDetection != nullptr)
			collisionDetection->AddCollider(collider);
	}

	if (ComponentTypes & ComponentType::actorRenderer)
	{
		ActorRenderer* renderer = new ActorRenderer(newActor);
		newActor->AddComponent(renderer);
	
		actorComponents.push_back(renderer);
	}

	if (ComponentTypes & ComponentType::animator)
	{
		Animator* anim = new Animator(newActor);
		newActor->AddComponent(anim);

		actorComponents.push_back(anim);
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
