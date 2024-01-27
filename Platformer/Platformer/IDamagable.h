#ifndef IDAMAGABLE_H
#define IDAMAGABLE_H

class IDamagable
{
public:
	virtual void TakeDamage(float damage, bool knockback) = 0;  // Pure virtual function
	virtual ~IDamagable() {}
};
#endif // !IDAMAGABLE_H