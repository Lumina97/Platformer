#include "Combat.h"
#include "CollisionDetection.h"
#include "Debug.h"
#include "Animator.h"
#include "Log.h"
#include "Entity.h"
#include "Actor.h"
#include "Collider.h"
#include "Globals.h"


Combat::Combat(Actor* Parent)
{
	attackSize = sf::Vector2f(50.0f, 60.0f);
	this->parent = Parent;
	AttackSequence = 0;
	anim = parent->GetComponent<Animator>();
	attackCoolDown = 0.65f;
	lastAttack = TIME::currentTime - attackCoolDown;
	damage = 5;
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

	AttackSequence++;
	PlayAttackAnimation();

	float top = parent->getPosition().y - parent->GetSize().y / 2 - attackSize.y / 2;
	float left = parent->getPosition().x;
	if (attackDirection > 0) left = left - parent->GetSize().x / 2 - attackOffset - attackSize.x;
	else if (attackDirection < 0)left += parent->GetSize().x / 2 + attackOffset;

	sf::Vector2f attackStart(left, top);

	std::vector<Physics::Collider*> hits = Physics::CollisionDetection::BoxCastAll(attackStart, parent->getRotation(), attackSize);
	Debug::DrawDebugBox(attackStart, sf::Vector2f(0, 0), parent->getRotation(), attackSize, 2, sf::Color::Transparent, sf::Color::Red, 2, 1);

	for (int i = 0; i < hits.size(); i++)
	{
		if (hits[i]->GetParentActor() == parent) {
			LOG_INFO("HIT SELF!");
			return;
		}

		Entity* entity = dynamic_cast<Entity*>(hits[i]->GetParentActor());
		if (entity != nullptr)
			entity->TakeDamage(damage);		
	}
}