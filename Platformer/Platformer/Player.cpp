#include "Player.h"
#include <iostream>
#include "Globals.h"
#include "CollisionDetection.h"

using namespace sf;

void Player::UpdateActor()
{
	ApplyMovement();
	isCollision = Physics::CollisionDirection::none;
}

void Player::OnCollision(Physics::CollisionDirection direction, float overlapAmount, Physics::Collider* other)
{	
	FloatRect bounds = other->GetBounds();
	Vector2f pos = getPosition();
	isCollision = direction;
	if (overlapAmount == 0) return;

	if (direction & Physics::CollisionDirection::left)
	{
		velocity.x = 0;
		setPosition(pos.x + overlapAmount, pos.y);
	}
	else if (direction & Physics::CollisionDirection::right)
	{
		velocity.x = 0;		
		setPosition(other->GetBounds().left - (size.x - getOrigin().x), pos.y);
	}

	else if (direction & Physics::CollisionDirection::top)
	{
		velocity.y = 0;
		setPosition(pos.x, pos.y - overlapAmount);
	}
	else if (direction & Physics::CollisionDirection::bottom)
	{
		velocity.y = 0;
		setPosition(pos.x, pos.y + overlapAmount);
	}
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
	wantsToJump = value;
}

bool Player::GetWantsToJump()
{
	return wantsToJump;
}

void Player::SetInputVector(sf::Vector2f input)
{
	InputVector = input;
	velocity = sf::Vector2f(0, 0);

	if (isCollision & Physics::CollisionDirection::left && InputVector.x < 0)	
		InputVector.x = 0;	
	if (isCollision & Physics::CollisionDirection::right && InputVector.x > 0)	
		InputVector.x = 0;
	if (isCollision & Physics::CollisionDirection::top && InputVector.y < 0)	
		InputVector.y = 0;	
	if (isCollision & Physics::CollisionDirection::bottom && InputVector.y > 0)	
		InputVector.y = 0;
	

	//CalculateVerticalMovement();
	float speedx = GetInputVector().x * GetMovementSpeed();
	float speedy = GetInputVector().y * GetMovementSpeed();

	velocity = sf::Vector2f(speedx, speedy);
	velocity *= TIME::DeltaTime;
}

sf::Vector2f Player::GetInputVector()
{
	return InputVector;
}

bool Player::IsGrounded()
{
	bool b = CollisionDetection::IsColliding(GetCollider());

	return b;
}

void Player::CalculateVerticalMovement()
{
	if (IsGrounded())
	{
		if (GetWantsToJump())
		{
			verticalSpeed = jumpForce;
			SetWantsToJump(false);
		}
		else
		{
			verticalSpeed = GLOBAL::gravity;
		}
	}
	else
	{
		verticalSpeed += GLOBAL::gravity;
	}

}

void Player::ApplyMovement()
{
	move(velocity);
}

Physics::Collider* Player::GetCollider()
{
	if (collider == nullptr)
	{
		collider = GetComponent<Physics::Collider>();
	}

	return collider;
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
