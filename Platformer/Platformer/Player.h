#ifndef  PLAYER
#define PLAYER

#include "Entity.h"
#include "Actor.h"

class Player :
    public Entity
{

public:
	Player(sf::Vector2f position, sf::Vector2f size, std::string name)
		: Entity(position, size, name) {
		Init();
	}





};
#endif // ! Player