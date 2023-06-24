#include "Combat.h"
#include "CollisionDetection.h"
#include "Debug.h"
#include "Animator.h"

Combat::Combat(Actor* Parent)
{
	attackSize = sf::Vector2f(50.0f, 60.0f);
	this->parent = Parent;
	AttackSequence = 0;
	anim = parent->GetComponent<Animator>();
	attackSequenceCooldown = 1.0f;
	attackSequenceStart = TIME::currentTime - attackSequenceCooldown;
	attackCoolDown = 0.5f;
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

	std::string attackAnimName = "Attack" + std::to_string(AttackSequence);
	AnimationTransitions transition;
	transition.finishAnimationBeforeSwitching = true;
	transition.fromAnimation = GetAnimator()->GetAnimationByName(attackAnimName);

	if (AttackSequence == 2)
	{
		transition.toAnimation = GetAnimator()->GetAnimationByName("Idle");
		transition.setNewToAnimation = true;
	}
	else if (AttackSequence == 1)
	{
		transition.toAnimation = GetAnimator()->GetAnimationByName("Attack2");
		transition.setNewToAnimation = true;
	}

	GetAnimator()->SwitchAnimation(attackAnimName, transition);
}

void Combat::Attack(int attackDirection)
{
	if (lastAttack + attackCoolDown > TIME::currentTime) return;
	
	lastAttack = TIME::currentTime;

	if (attackSequenceStart + attackSequenceCooldown > TIME::currentTime)
		AttackSequence = 1;

	float top = getPosition().y - parent->GetSize().y / 2 - attackSize.y / 2;
	float left = getPosition().x;
	if (attackDirection > 0) left = left - parent->GetSize().x / 2 - attackOffset - attackSize.x;
	else if (attackDirection < 0)left += parent->GetSize().x / 2 + attackOffset;

	sf::Vector2f attackStart(left, top);

	Physics::CollisionDetection::BoxCast(attackStart, getRotation(), attackSize);
	Debug::DrawDebugBox(attackStart, sf::Vector2f(0, 0), getRotation(), attackSize);


	AttackSequence++;
	PlayAttackAnimation();
}
