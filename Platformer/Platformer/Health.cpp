#include "Health.h"
#include "Log.h"

Health::Health(float amount, std::function<void(void)> onDeathFunction)
{
	this->maxHealth = amount;
	this->onDeath = onDeathFunction;
	this->isDead = false;
}

Health::~Health()
{

}

void Health::TakeDamage(float damage, bool knockback)
{
	if (GetIsDead()) {
		LOG_INFO("ALREADY DED! PLS STOP!!");
		return;
	}

	LOG_INFO("TOOK DAMAGE! {0}", damage);
	maxHealth -= damage;
	if (maxHealth <= 0 )
	{
		isDead = true;
		if(onDeath != nullptr) onDeath();
	}

}

bool Health::GetIsDead()
{
	return isDead;
}
