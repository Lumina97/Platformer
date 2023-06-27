#include "Enemy.h"
#include <iostream>
#include "Globals.h"
#include "CollisionDetection.h"
#include "Debug.h"
#include "Log.h"

using namespace sf;

Enemy::~Enemy()
{
	delete(combat);
}

void Enemy::UpdateActor()
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

void Enemy::Dash()
{
	if (isDashing || lastDashEnd + dashCooldown > TIME::currentTime) return;
	if (InputVector.x == 0 && InputVector.y == 0) return;

	dashStartTime = TIME::currentTime;
	isDashing = true;
	dashDirection = InputVector;
	dashDirection.y = velocity.y;

	velocity = InputVector;
}

void Enemy::Attack()
{
	if (combat)
	{
		combat->Attack(isFlipped ? 1 : -1);
	}
}
void Enemy::TakeDamage(float amount)
{
	if (health == nullptr)
	{
		LOG_WARN("No health component attached! - Player - TakeDamage");
		return;
	}

	health->TakeDamage(amount, false);
}

void Enemy::OnDeath()
{
	LOG_INFO("DED");
	GetAnimator()->AddAnimationToQ(GetAnimator()->GetAnimationByName("Death"));
	GetAnimator()->AddAnimationToQ(GetAnimator()->GetAnimationByName("Dead"));
}

void Enemy::CalculateVerticalMovement()
{
	if (isGrounded)
	{
		if (GetWantsToJump())
		{
			verticalSpeed = -jumpForce;
			SetWantsToJump(false);
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

void Enemy::ApplyMovement()
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

	sf::FloatRect collision = Physics::CollisionDetection::WillCollideInDirection(GetCollider());
	if (collision.left != -1 && collision.top != -1)
	{
		float amount = 0;
		sf::Vector2f pos = getPosition();
		isCollision = Physics::CollisionDetection::GetOverlapAmount(GetNextBounds(), collision, amount);

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
			setPosition(pos.x, collision.top);
		}
		if (isCollision & Physics::CollisionDirection::bottom && velocity.y < 0)
		{
			velocity.y = 0;
			setPosition(pos.x, collision.top + collision.height + getOrigin().y);
		}
	}
	else
		isGrounded = false;

	move(velocity);
}

#pragma region Getter & Setters
Physics::Collider* Enemy::GetCollider()
{
	if (collider == nullptr)
	{
		collider = GetComponent<Physics::Collider>();
	}

	return collider;
}
Animator* Enemy::GetAnimator()
{
	if (anim == nullptr)
	{
		anim = GetComponent<Animator>();
	}

	return anim;
}
sf::FloatRect Enemy::GetNextBounds()
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

void Enemy::SetMovementSpeed(float speed)
{
	movementSpeed = speed;
}
float Enemy::GetMovementSpeed()
{
	return movementSpeed;
}

void Enemy::SetWantsToJump(bool value)
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
bool Enemy::GetWantsToJump()
{
	return wantsToJump;
}

void Enemy::SetInputVector(sf::Vector2f input)
{
	InputVector = input;
}
sf::Vector2f Enemy::GetInputVector()
{
	return InputVector;
}
#pragma endregion