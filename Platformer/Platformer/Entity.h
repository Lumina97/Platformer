#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Collider.h"
#include "Animator.h"
#include "Combat.h"
#include "Health.h"
#include "GameGUI.h"

class Entity : public Actor 
{	
public:
	Entity(sf::Vector2f position, sf::Vector2f size, std::string name)
		: Actor(position, size, name) {
		Init();
	}
	~Entity();

	// Inherited via Actor
	virtual void UpdateActor() override;
	virtual sf::FloatRect GetNextBounds() override;
	float GetMovementSpeed();
	void SetMovementSpeed(float speed);
	void SetWantsToJump(bool value);
	bool GetWantsToJump();
	void SetInputVector(sf::Vector2f input);
	sf::Vector2f GetInputVector();
	sf::Vector2f GetVelocity();
	void SetGUI(GameGUI* gui);
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
	void CheckNextMoveCollisions();

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
	float TakeDamageCooldown;
	float lastDamageTaken;

private:
	Physics::CollisionDirection isCollision;
	sf::Vector2f velocity;
	sf::Vector2f dashDirection;
	sf::Vector2f InputVector;	
	Physics::Collider* collider;
	Animator* anim;
	Combat* combat;
	Health* health;
	GameGUI* gui;
};
#endif // !PLAYER_H