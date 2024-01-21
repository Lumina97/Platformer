#include "Component.h"
#include "Actor.h"
#include "Log.h"

Component::Component(Actor* actorToAttachTo)
{
	if (actorToAttachTo != nullptr)
	{
		parentActor = actorToAttachTo;
	}
}

void Component::UpdateComponent()
{
	if (parentActor == nullptr) {
		LOG_ERROR("PARENT IS NULL!");
		return;
	}

	//moved
	if (getPosition() != parentActor->getPosition())
		hasMoved = true;
	else
		hasMoved = false;


	//moved
	if (getRotation() != parentActor->getRotation())
		hasMoved = true;
	else if(hasMoved != true)
		hasMoved = false;

	setOrigin(parentActor->getOrigin());
	setPosition(parentActor->getPosition());
	setRotation(parentActor->getRotation());
	setScale(parentActor->getScale());
}

bool Component::GetHasMoved()
{
	return hasMoved;
}

Actor* Component::GetParentActor()
{
	return parentActor;
}

ComponentType Component::GetComponentType()
{
	return type;
}

void Component::SetActive(bool isActive)
{
	LOG_INFO("Disabled Collider!");
	activeState = isActive;
}

bool Component::GetIsActive()
{
	return activeState;
}
