#include "EnemyAI.h"
#include "Log.h"
#include "Globals.h"
#include "Entity.h"

EnemyAI::EnemyAI(Entity* Enemy, Entity* player)
{
	this->player = player;
	this->enemy = Enemy;
	attackDelay = 1.5f;
	lastAttack = 0;
}

void EnemyAI::Update()
{
	float dist = GetDistanceToPlayer();
	enemy->SetInputVector(sf::Vector2f(0, 0));
	if (std::abs(dist) > 120)
	{
		Move();
	}
	else if (lastAttack + attackDelay < TIME::currentTime)
	{
		lastAttack = TIME::currentTime;
		enemy->Attack();
	}
}

float EnemyAI::GetMoveDirection()
{
	if (player == nullptr) 
	{
		LOG_WARN("Player was not set for ENEMY AI");
		return 0 ;
	}

	float dir =  player->getPosition().x - enemy->getPosition().x;
	dir  = std::clamp(dir, -1.0f, 1.0f);
	return dir;
}

float EnemyAI::GetDistanceToPlayer()
{
	if (player == nullptr)
	{
		LOG_WARN("Player was not set for ENEMY AI");
		return 0;
	}

	float dir = player->getPosition().x - enemy->getPosition().x;
	return dir;
}

void EnemyAI::Move()
{
	if (enemy == nullptr)
	{
		LOG_WARN("ENEMY was not passed in to AI");
		return;
	}
	float dir = GetMoveDirection();
	enemy->SetInputVector(sf::Vector2f(dir, 0));
}