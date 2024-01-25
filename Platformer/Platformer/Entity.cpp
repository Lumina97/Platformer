#include "Entity.h"
#include <iostream>
#include "Globals.h"
#include "CollisionDetection.h"
#include "Debug.h"
#include "Log.h"
#include "Actor.h"
#include "Collider.h"
#include "Animator.h"
#include "Combat.h"
#include "GameGUI.h"
#include "Health.h"

using namespace sf;

void Entity::Init()
{
	SetMovementSpeed(300.0f);
	jumpForce = 800.0f;
	dashSpeed = movementSpeed * 3;
	dashTime = 0.35f;
	dashCooldown = 2.0f;
	TakeDamageCooldown = 0.3f;
	combat = new Combat(this);
	health = new Health(10, std::bind(&Entity::OnDeath, this));
}

Entity::~Entity()
{
	delete(combat);
	delete(health);
	Actor::~Actor();
}

void Entity::UpdateActor()
{
	if (getPosition().y > GLOBAL::ScreenSize.y * 1.5f &&
		(health != nullptr && health->GetIsDead() == false)) {
		TakeDamage(9999);
	}

	if (health != nullptr && health->GetIsDead()) return;

	Vector2f pos = getPosition();
	Vector2f origin = getOrigin();

	Debug::DrawDebugBox(getPosition(), getOrigin(), getRotation(), size);

	ApplyMovement();
}

void Entity::Dash()
{
	if (isDashing || lastDashEnd + dashCooldown > TIME::currentTime) return;
	if (InputVector.x == 0 && InputVector.y == 0) return;

	dashStartTime = TIME::currentTime;
	isDashing = true;
	dashDirection = InputVector;
	dashDirection.y = velocity.y;

	velocity = InputVector;
}

void Entity::Attack()
{
	if (health && health->GetIsDead() == true) return;

	if (combat)
	{
		combat->Attack(isFlipped ? 1 : -1);
	}
}

void Entity::TakeDamage(float amount)
{
	if (health == nullptr)
	{
		LOG_WARN("No health component attached! - Player - TakeDamage");
		return;
	}

	if (lastDamageTaken + TakeDamageCooldown > TIME::currentTime)
		return;


	lastDamageTaken = TIME::currentTime;
	health->TakeDamage(amount, false);
	if (gui) gui->ChangeHealth(health->GetCurrentHealth());
}

void Entity::OnDeath()
{
	LOG_INFO("DEAD");
	GetAnimator()->AddAnimationToQ(GetAnimator()->GetAnimationByName("Death"));
	GetAnimator()->AddAnimationToQ(GetAnimator()->GetAnimationByName("Dead"));
	GetCollider()->SetActive(false);

	if (gui) gui->SetGameOverScreen(true);
	if (gui) gui->SetGameElementsScreenVisible(false);
}


void Entity::CalculateVerticalMovement()
{
	if (isGrounded)
	{
		if (GetWantsToJump())
		{
			verticalSpeed = -jumpForce;
			SetWantsToJump(false);
			isGrounded = false;
		}
		else
		{
			verticalSpeed = GLOBAL::gravity / 3;
		}
	}
	else
	{
		verticalSpeed += GLOBAL::gravity;
	}
}


void Entity::CheckNextMoveCollisions()
{
	std::vector<sf::FloatRect> collisions = Physics::CollisionDetection::WillCollideInDirection(GetCollider());
	if (collisions.size() == 0)
		isGrounded = false;

	for (int i = 0; i < collisions.size(); i++)
	{
		sf::FloatRect collision = collisions[i];
		sf::Vector2f pos = getPosition();
		isCollision = Physics::CollisionDetection::GetOverlapAmount(GetNextBounds(), collision);

		if (isCollision & Physics::CollisionDirection::left && velocity.x < 0)
		{
			velocity.x = 0;
			setPosition(collision.left + collision.width + getOrigin().x, pos.y);
		}
		if (isCollision & Physics::CollisionDirection::right && velocity.x > 0)
		{
			velocity.x = 0;
			setPosition(collision.left - getOrigin().x, pos.y);
		}
		if (isCollision & Physics::CollisionDirection::top && velocity.y > 0)
		{
			isGrounded = true;
			velocity.y = 0;
			verticalSpeed = velocity.y;
			setPosition(pos.x, collision.top);
		}
		if (isCollision & Physics::CollisionDirection::bottom && velocity.y < 0)
		{
			velocity.y = 0;
			verticalSpeed = velocity.y;
			setPosition(pos.x, collision.top + collision.height + getOrigin().y);
		}
	}
}

void Entity::ApplyMovement()
{

	float currentTime = TIME::currentTime;
	if (isDashing == false)
	{
		CalculateVerticalMovement();
		float speedx = GetInputVector().x * GetMovementSpeed();

		if (speedx != 0)  GetAnimator()->AddAnimationToQ(GetAnimator()->GetAnimationByName("Run"));
		else GetAnimator()->AddAnimationToQ(GetAnimator()->GetAnimationByName("Idle"));

		//flip sprite
		if (speedx < 0)isFlipped = true;
		if (speedx > 0)isFlipped = false;
		GetAnimator()->Flip(isFlipped);


		velocity = sf::Vector2f(speedx, verticalSpeed);
		velocity *= TIME::DeltaTime;
	}
	else if (isDashing && dashStartTime + dashTime > currentTime)
	{
		velocity = dashDirection;
		velocity.y += GLOBAL::gravity / 4;
		velocity *= dashSpeed * TIME::DeltaTime;
	}
	else if (isDashing && dashStartTime + dashTime < currentTime)
	{
		verticalSpeed = velocity.y;

		lastDashEnd = currentTime;
		isDashing = false;
	}
	CheckNextMoveCollisions();

	move(velocity);
}


#pragma region Getter & Setters
Physics::Collider* Entity::GetCollider()
{
	if (collider == nullptr)
	{
		collider = GetComponent<Physics::Collider>();
	}

	return collider;
}
Animator* Entity::GetAnimator()
{
	if (anim == nullptr)
	{
		anim = GetComponent<Animator>();
	}

	return anim;
}

sf::FloatRect Entity::GetNextBounds()
{
	if (GetCollider())
	{

		Vector2f topLeft = getPosition();
		topLeft -= getOrigin();
		topLeft += velocity;
		sf::FloatRect bounds(topLeft.x, topLeft.y, size.x, size.y);

		return bounds;
	}

	return sf::FloatRect();
}

void Entity::SetMovementSpeed(float speed)
{
	movementSpeed = speed;
}
float Entity::GetMovementSpeed()
{
	return movementSpeed;
}

void Entity::SetWantsToJump(bool value)
{
	if (isGrounded)
	{
		wantsToJump = value;
		if (wantsToJump)
			SetInputVector(sf::Vector2f(GetInputVector().x, 1));
	}
	else
		wantsToJump = false;
}
bool Entity::GetWantsToJump()
{
	return wantsToJump;
}

void Entity::SetInputVector(sf::Vector2f input)
{
	InputVector = input;
}
sf::Vector2f Entity::GetInputVector()
{
	return InputVector;
}
sf::Vector2f Entity::GetVelocity()
{
	return velocity;
}
void Entity::SetGUI(GameGUI* gui)
{
	this->gui = gui;
	this->gui->ChangeHealth(health->GetCurrentHealth());
}
#pragma endregion