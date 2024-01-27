#ifndef  COMPONENT_H
#define COMPONENT_H

#include "SFML/Graphics.hpp"

class Actor;

enum ComponentType
{
	animator = 1,
	actorRenderer = 2,
	collider = 4
};
inline ComponentType operator|(ComponentType a, ComponentType b)
{
	return static_cast<ComponentType>(static_cast<int>(a) | static_cast<int>(b));
}

class Component : public sf::Transformable
{
public:
	Component() {};
	Component(Actor* actorToAttachTo);
	~Component() {};

	virtual void UpdateComponent();
	bool GetHasMoved();
	Actor* GetParentActor();
	ComponentType GetComponentType();
	void SetActive(bool isActive);
	bool GetIsActive();

protected:
	ComponentType type;
	Actor* parentActor = nullptr;
	bool hasMoved = false;
	bool activeState = true;


};

#endif // ! COMPONENT_H
