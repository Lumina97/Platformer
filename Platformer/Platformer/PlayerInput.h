#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H

class Entity;

class PlayerInput
{

public :
	PlayerInput(Entity* controllingPlayer);
	void Update();


private:
	Entity* player;

};
#endif // !PLAYERINPUT_H