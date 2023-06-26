#include "Combat.h"
#include "CollisionDetection.h"
#include "Debug.h"
#include "Animator.h"
#include "Log.h"

Combat::Combat(Actor* Parent)
{
	attackSize = sf::Vector2f(50.0f, 60.0f);
	this->parent = Parent;
	AttackSequence = 0;
	anim = parent->GetComponent<Animator>();
	attackCoolDown = 0.65f;
	lastAttack = TIME::currentTime - attackCoolDown;
}


Animator* Combat::GetAnimator()
{
	if (anim == nullptr)
	{
		anim = parent->GetComponent<Animator>();
	}

	return anim;
}

void Combat::PlayAttackAnimation()
{
	if (AttackSequence > 2)
		AttackSequence = 1;

	LOG_INFO("Attack: {0}", AttackSequence);
	std::string attackAnimName = "Attack" + std::to_string(AttackSequence);
	GetAnimator()->AddAnimationToQ(GetAnimator()->GetAnimationByName(attackAnimName));
}

void Combat::Attack(int attackDirection)
{
	if (lastAttack + attackCoolDown > TIME::currentTime) return;
	
	lastAttack = TIME::currentTime;

	float top = parent->getPosition().y - parent->GetSize().y / 2 - attackSize.y / 2;
	float left = parent->getPosition().x;
	if (attackDirection > 0) left = left - parent->GetSize().x / 2 - attackOffset - attackSize.x;
	else if (attackDirection < 0)left += parent->GetSize().x / 2 + attackOffset;

	sf::Vector2f attackStart(left, top);

	Physics::CollisionDetection::BoxCast(attackStart, parent->getRotation(), attackSize);
	Debug::DrawDebugBox(attackStart, sf::Vector2f(0,0), parent->getRotation(), attackSize,attackCoolDown,sf::Color::Transparent,sf::Color::White,1,1);


	AttackSequence++;
	PlayAttackAnimation();
}
