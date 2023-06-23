#include "ComponentManager.h"


ComponentManager::ComponentManager(sf::RenderWindow* renderWindow)
{
	this->window = renderWindow;
	collisionDetection = new CollisionDetection();

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
	if (collisionDetection != nullptr) collisionDetection->UpdateCollision();

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