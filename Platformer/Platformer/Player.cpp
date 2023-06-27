#include "Player.h"
#include <iostream>
#include "Globals.h"
#include "CollisionDetection.h"
#include "Debug.h"
#include "Log.h"

using namespace sf;

Player::~Player()
{
	delete(combat);
	delete(health);
}

void Player::UpdateActor()
{
	Vector2f pos = getPosition();
	Vector2f origin = getOrigin();

	Debug::DrawDebugBox(getPosition(), getOrigin(), getRotation(), size);
	ApplyMovement();
}

void Player::Dash()
{
	if (isDashing || lastDashEnd + dashCooldown > TIME::currentTime) return;
	if (InputVector.x == 0 && InputVector.y == 0) return;

	dashStartTime = TIME::currentTime;
	isDashing = true;
	dashDirection = InputVector;
	dashDirection.y = velocity.y;

	velocity = InputVector;
}

void Player::Attack()
{
	if (combat)
	{
		combat->Attack(isFlipped ? 1 : -1);
	}
}

void Player::TakeDamage(float amount)
{
	if (health == nullptr)
	{
		LOG_WARN("No health component attached! - Player - TakeDamage");
		return;
	}
	LOG_INFO("PLAYER TOOK DAMAGE! {0}", amount);
	health->TakeDamage(amount, false);
}

void Player::OnDeath()
{
	LOG_INFO("DED");
}

void Player::CalculateVerticalMovement()
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

void Player::ApplyMovement()
{	
	float currentTime = TIME::currentTime;
	if (isDashing == false)
	{
		CalculateVerticalMovement();
		float speedx = GetInputVector().x * GetMovementSpeed();

		if (speedx != 0)  GetAnimator()->AddAnimationToQ(GetAnimator()->GetAnimationByName("Run"));
		else GetAnimator()->AddAnimationToQ(GetAnimator()->GetAnimationByName( "Idle"));

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
		velocity *= dashSpeed *TIME::DeltaTime;
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
	GLOBAL::CAMERA->move(velocity);
	sf::Vector2f camPos = getPosition();
	camPos.y -= 250.0f;
	GLOBAL::CAMERA->setCenter(camPos);
	GLOBAL::WINDOW->setView(*GLOBAL::CAMERA);
}

#pragma region Getter & Setters
Physics::Collider* Player::GetCollider()
{
	if (collider == nullptr)
	{
		collider = GetComponent<Physics::Collider>();
	}

	return collider;
}
Animator* Player::GetAnimator()
{
	if (anim == nullptr)
	{
		anim = GetComponent<Animator>();
	}

	return anim;
}
sf::FloatRect Player::GetNextBounds()
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

void Player::SetMovementSpeed(float speed)
{
	movementSpeed = speed;
}
float Player::GetMovementSpeed()
{
	return movementSpeed;
}

void Player::SetWantsToJump(bool value)
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
bool Player::GetWantsToJump()
{
	return wantsToJump;
}

void Player::SetInputVector(sf::Vector2f input)
{
	InputVector = input;
}
sf::Vector2f Player::GetInputVector()
{
	return InputVector;
}
#pragma endregion