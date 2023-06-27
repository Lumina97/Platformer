#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Collider.h"
#include "Animator.h"
#include "Combat.h"
#include "Health.h"

class Player : public Actor 
{	
public:
	Player(sf::Vector2f position, sf::Vector2f size, std::string name)
		: Actor(position, size, name) {
		Init();
	}
	~Player();

	// Inherited via Actor
	virtual void UpdateActor() override;
	virtual sf::FloatRect GetNextBounds() override;
	float GetMovementSpeed();
	void SetMovementSpeed(float speed);
	void SetWantsToJump(bool value);
	bool GetWantsToJump();
	void SetInputVector(sf::Vector2f input);
	sf::Vector2f GetInputVector();
	void Dash();
	void Attack();
	void TakeDamage(float amount);
	void OnDeath();

private:	
	void CalculateVerticalMovement();
	void ApplyMovement();
	void Init();
	Physics::Collider* GetCollider();
	Animator* GetAnimator();


private:
	float movementSpeed;
	float jumpForce;
	float desiredMoveSpeed;
	float verticalSpeed;
	float dashSpeed;
	bool wasGrounded;	
	bool wantsToJump;
	bool isGrounded;
	bool isDashing;
	float dashTime;
	float dashStartTime;
	float dashCooldown;
	float lastDashEnd;
	bool isFlipped;

private:
	Physics::CollisionDirection isCollision;
	sf::Vector2f velocity;
	sf::Vector2f dashDirection;
	sf::Vector2f InputVector;	
	Physics::Collider* collider;
	Animator* anim;
	Combat* combat;
	Health* health;
};
#endif // !PLAYER_H