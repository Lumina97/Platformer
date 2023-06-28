#pragma once
#include "Entity.h"
class EnemyAI
{
public:
	EnemyAI(Entity* Enemy, Entity* player);

	void Update();

private:
	float GetMoveDirection();
	float GetDistanceToPlayer();
	void Move();


private:
	Entity* player;
	Entity* enemy;
	float attackDelay;
	float lastAttack;
};

