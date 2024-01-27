#ifndef PLAYER_H
#define PLAYER_H

#include  "Actor.h";

class Collider;
class Animator;
class Combat;
class GameGUI;
class Health;

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
	virtual float GetMovementSpeed();
	virtual void SetMovementSpeed(float speed);
	virtual void SetWantsToJump(bool value);
	virtual bool GetWantsToJump();
	virtual void SetInputVector(sf::Vector2f input);
	virtual sf::Vector2f GetInputVector();
	virtual sf::Vector2f GetVelocity();
	virtual void SetGUI(GameGUI* gui);
	virtual void Dash();
	virtual void Attack();
	virtual void TakeDamage(float amount);
	virtual void OnDeath();

protected:
	void CalculateVerticalMovement();
	void ApplyMovement();
	void Init();
	Physics::Collider* GetCollider();
	Animator* GetAnimator();
	void CheckNextMoveCollisions();

protected:
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

protected:
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