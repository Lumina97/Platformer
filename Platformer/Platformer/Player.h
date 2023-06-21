#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Collider.h"

class Player : public Actor 
{	
public:
	Player(sf::Vector2f position, sf::Vector2f size, std::string name)
		: Actor(position, size, name) {
		SetMovementSpeed(200.0f);
		jumpForce = 500.0f;
	}

	// Inherited via Actor
	virtual void UpdateActor() override;
	virtual void OnCollision(Physics::CollisionDirection direction, float overlapAmount, Physics::Collider* other) override;
	virtual sf::FloatRect GetNextBounds() override;
	float GetMovementSpeed();
	void SetMovementSpeed(float speed);
	void SetWantsToJump(bool value);
	bool GetWantsToJump();
	void SetInputVector(sf::Vector2f input);
	sf::Vector2f GetInputVector();

private:	
	bool IsGrounded();
	void CalculateVerticalMovement();
	void ApplyMovement();
	Physics::Collider* GetCollider();

private:
	float movementSpeed;
	float jumpForce;
	float desiredMoveSpeed;
	float verticalSpeed;
	bool wasGrounded;	
	bool wantsToJump;
	
private:
	Physics::CollisionDirection isCollision;
	sf::Vector2f velocity;
	sf::Vector2f InputVector;	
	Physics::Collider* collider;
};
#endif // !PLAYER_H