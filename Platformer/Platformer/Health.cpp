#include "Health.h"
#include "Log.h"

Health::Health(float amount, std::function<void(void)> onDeathFunction)
{
	this->maxHealth = amount;
	this->onDeath = onDeathFunction;
	this->isDead = false;
	this->currentHealth = maxHealth;
}

Health::~Health(){}

void Health::TakeDamage(float damage, bool knockback)
{
	if (GetIsDead()) {
		LOG_INFO("ALREADY DED! PLS STOP!!");
		return;
	}

	LOG_INFO("TOOK DAMAGE! {0}", damage);
	currentHealth -= damage;
	if (currentHealth <= 0 )
	{
		isDead = true;
		if(onDeath != nullptr) onDeath();
	}

}

bool Health::GetIsDead()
{
	return isDead;
}

float Health::GetCurrentHealth()
{
	return currentHealth;
}

void Health::ResetHealth()
{
	currentHealth = maxHealth;
}
