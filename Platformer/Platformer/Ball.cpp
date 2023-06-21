#include "Ball.h"
#include "Globals.h"
#include "Math.h"
#include <iostream>

void Ball::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	sf::Vector2f nextPos = getPosition();
	nextPos += velocity * movementSpeed * TIME::DeltaTime;

	setPosition(nextPos);
}

void Ball::OnCollision(float angle)
{
	sf::Vector2f newVel = velocity;
	newVel.x *= -1;
	newVel.y += (angle * angle)   * -0.1f;
	SetVelocity(newVel);
}

void Ball::OnScreenCollision()
{
	sf::Vector2f newVel = velocity;	
	newVel.y *= -1.0f;
	SetVelocity(newVel);
}

bool Ball::GetIsMoving()
{
	return (velocity.x != 0 && velocity.y != 0);
}

void Ball::SetIsMoving(bool value)
{
	isMoving = value;
	if (isMoving == false)
	{
		velocity = sf::Vector2f(0, 0);
	}
}

sf::Vector2f Ball::GetVelocity()
{
	return velocity;
}

void Ball::SetVelocity(sf::Vector2f velocity)
{
	velocity = MATH::Normalized(velocity);
	this->velocity = velocity;
}

void Ball::SetVelocity(float velocity)
{
	this->velocity = sf::Vector2f(velocity, velocity);
	this->velocity = MATH::Normalized(this->velocity);
}

bool Ball::IsTravelingRight()
{
	if (velocity.x > 0) return true;
	return false;
}
