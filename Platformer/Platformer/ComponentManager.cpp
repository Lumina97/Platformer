#include "ComponentManager.h"


std::vector<Actor*> ComponentManager::sceneActors;
std::vector<Animator*> ComponentManager::animators;
std::vector<Component*> ComponentManager::actorComponents;


ComponentManager::ComponentManager(sf::RenderWindow* renderWindow, Physics::CollisionDetection* collisionDetection)
{
	this->window = renderWindow;
	this->collisionDetection = collisionDetection;
}

void ComponentManager::SetPlayerInput(PlayerInput* input)
{
	this->input = input;
}

void ComponentManager::UpdateComponents()
{
	//player input
	if (input != nullptr) input->Update();

	//collision
	if (collisionDetection != nullptr)
		collisionDetection->UpdateCollision();

	//update actors
	for (int i = 0; i < sceneActors.size(); i++)
	{
		if (sceneActors[i] != nullptr)
		{
			sceneActors[i]->UpdateActor();
		}
	}

	//update components
	for (int i = 0; i < actorComponents.size(); i++)
	{
		if (actorComponents[i] != nullptr)
		{
			actorComponents[i]->UpdateComponent();
		}
	}

	//update animators
	if (animators.empty() == false)
	{
		for (int i = 0; i < animators.size(); i++)
		{
			if (animators[i] != nullptr)
			{
				animators[i]->UpdateComponent();
			}
		}
	}
}

void ComponentManager::Destroy(Actor* actor)
{
	std::_Vector_iterator id = std::find(sceneActors.begin(), sceneActors.end(), actor);
	if (id != sceneActors.end())
	{
		delete(actor);
		sceneActors.erase(id);
	}
}

void ComponentManager::Destroy(Component* Component)
{
	std::_Vector_iterator id = std::find(actorComponents.begin(), actorComponents.end(), Component);
	if (id != actorComponents.end())
	{		
		if(Component->GetComponentType() & ComponentType::animator)
		{		
			std::_Vector_iterator animId = std::find(animators.begin(), animators.end(), Component);
			if (animId != animators.end())
			{
				animators.erase(animId);
			}
		}

		delete(Component);
		actorComponents.erase(id);
	}
}