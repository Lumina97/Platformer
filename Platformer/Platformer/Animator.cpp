#include "Animator.h"
#include <iostream>
#include "Debug.h"
#include "Globals.h"

Animator::Animator( Actor* parentActor)
{
	this->parentActor = parentActor;
	this->type = ComponentType::animator;
	isFlipped = false;
}

Animator::~Animator()
{
	for (int i = 0; i < animations.size(); i++)
	{
		delete(animations[i]);
	}
	animations.clear();
}

void Animator::UpdateComponent()
{
	Component::UpdateComponent();

	//only update animations at set fps
	totalElapsed += clock.restart();
	if (totalElapsed.asSeconds() >= 1.0 / animationFPSTarget)
	{
		totalElapsed = clock.restart();
		animations[currentAnimation]->UpdateAnimation();
	}

	if (GLOBAL::WINDOW)
	{
		sf::Sprite sprite = *GetCurrentSprite();

		sf::Vector2f origin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 1.25f);
		sprite.setOrigin(origin);
		sprite.setPosition(getPosition());
		sprite.setRotation(getRotation());
		
		//Sprite flipping
		float scaleAmount = 2.0f;
		sf::Vector2f scale = getScale() * scaleAmount;
		if (isFlipped) scale.x *= -1.0f;
		sprite.setScale(scale);		

		//sf::Vector2f size(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
		//Debug::DrawDebugBox(sprite.getPosition(), origin,sprite.getRotation(),size,sf::Color::Transparent,sf::Color::White,1.0f, scaleAmount);
		GLOBAL::WINDOW->draw(sprite);
	}
}

void Animator::AddAnimation(Animation* animation)
{
	animations.push_back(animation);
}

void Animator::SwitchAnimation(std::string name)
{
	bool switchedAnimation = false;
	if (animations.empty()) return;
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations[i]->GetName() == name)
		{
			if (currentAnimation == i) return;

			currentAnimation = i;
			animations[i]->RestartAnimation();
			switchedAnimation = true;
		}
	}

	if (switchedAnimation == false)
	{
		std::cout << "Failed to switch animations to given name: " << name << "\n";
	}
}

sf::Sprite* Animator::GetCurrentSprite()
{
	return animations[currentAnimation]->GetCurrentAnimationFrame();
}

void Animator::Flip(bool Flipped)
{
	isFlipped = Flipped;
}
