#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Collider.h"
#include "Animator.h"

class Player : public Actor 
{	
public:
	Player(sf::Vector2f position, sf::Vector2f size, std::string name)
		: Actor(position, size, name) {
		SetMovementSpeed(350.0f);
		jumpForce = 1500.0f;
		dashSpeed = movementSpeed * 3;
		dashTime = 0.35f;
		dashCooldown = 2.0f;
	}

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

private:	
	void CalculateVerticalMovement();
	void ApplyMovement();
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

private:
	Physics::CollisionDirection isCollision;
	sf::Vector2f velocity;
	sf::Vector2f dashDirection;
	sf::Vector2f InputVector;	
	Physics::Collider* collider;
	Animator* anim;
};
#endif // !PLAYER_H