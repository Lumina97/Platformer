#ifndef  COMBAT_H
#define COMBAT_H

#include "SFML/Graphics.hpp"

class Animator;
class Actor;

class Combat
{
public:
	Combat(Actor* Parent);

	void Attack(int attackDirection);

private:
	Animator* GetAnimator();
	void PlayAttackAnimation();

private:
	Actor* parent;
	sf::Vector2f attackSize;
	Animator* anim;
	float attackOffset = 10.0f;
	int AttackSequence;
	float attackSequenceStart;
	float attackSequenceCooldown;

	float attackCoolDown;
	float lastAttack;
	float damage;
};

#endif // ! COMBAT_H
