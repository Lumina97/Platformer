#ifndef HEALTH_H
#define HEALTH_H

#include "IDamagable.h"
#include <functional>

using OnDeathCallbackFunction = std::function<void(void)>;

class Health : public IDamagable
{
public:

	Health(float amount, std::function<void(void)> onDeathFunction);
	~Health();

	// Inherited via IDamagable
	virtual void TakeDamage(float damage, bool knockback) override;
	bool GetIsDead();
	float GetCurrentHealth();
	void ResetHealth();

private:
	float maxHealth;
	float currentHealth;
	bool isDead;
	OnDeathCallbackFunction onDeath;
};

#endif // !HEALTH_H