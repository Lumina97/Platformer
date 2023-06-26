#include "PlayerInput.h"
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Log.h"

PlayerInput::PlayerInput(Player* controllingPlayer)
{
	player = controllingPlayer;
}

void PlayerInput::Update()
{
	if (player == nullptr) {
		LOG_ERROR("PLAYER NOT SET!");
		return;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		player->Attack();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		player->setPosition(GLOBAL::ScreenSize.x / 2, GLOBAL::ScreenSize.y / 2);

	float x = 0;
	float y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player->SetWantsToJump(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		player->Dash();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		x = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		x = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		y= -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		y = 1;

	player->SetInputVector(sf::Vector2f(x,y));
}
