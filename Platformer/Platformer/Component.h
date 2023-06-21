#ifndef  COMPONENT_H
#define COMPONENT_H

#include "SFML/Graphics.hpp"

class Actor;


class Component : public sf::Transformable
{
public:
	Component() {};
	Component(Actor* actorToAttachTo);
	virtual void UpdateComponent();
	bool GetHasMoved();
	Actor* GetParentActor();

protected:

	Actor* parentActor = nullptr;
	bool hasMoved = false;

};

#endif // ! COMPONENT_H
