#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H


#include "Player.h"
class PlayerInput
{

public :
	PlayerInput(Player* controllingPlayer);
	void Update();


private:
	Player* player;

};
#endif // !PLAYERINPUT_H