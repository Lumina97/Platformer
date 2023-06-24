#include "Animator.h"
#include <iostream>
#include "Debug.h"
#include "Globals.h"

Animator::Animator(Actor* parentActor)
{
	this->parentActor = parentActor;
	this->type = ComponentType::animator;
	isFlipped = false;
	lastTransition = {};
	animations = {};
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

		//check if animation was done playing and if an animation was Queued
		if (lastTransition.fromAnimation != nullptr && lastTransition.fromAnimation->GetFinishedPlaying() == true)
		{
			SwitchAnimation(lastTransition.toAnimation->GetName());
			lastTransition = {};
		}
	}
}

void Animator::AddAnimation(Animation* animation)
{
	animations.push_back(animation);
}

void Animator::SwitchAnimation(std::string name, AnimationTransitions transition)
{
	if (transition.setNewToAnimation)
		lastTransition.toAnimation = transition.toAnimation;

	if (lastTransition.fromAnimation == nullptr)
	{
		lastTransition = transition;
		int index = GetAnimationByIndex(name);
		if (index != currentAnimation && index >= 0 && index < animations.size())
		{
			currentAnimation = index;
			animations[index]->RestartAnimation();
		}
	}

	bool fromAnimationNotNull = lastTransition.fromAnimation != nullptr;
	bool finishedPlaying = fromAnimationNotNull && lastTransition.fromAnimation->GetFinishedPlaying();
	bool canInterrupt = lastTransition.finishAnimationBeforeSwitching;
	bool finishedPlayingOrCanInterrupt = (finishedPlaying || canInterrupt == false);

	if (fromAnimationNotNull && finishedPlayingOrCanInterrupt)
	{
		int index = GetAnimationByIndex(name);
		if (index != currentAnimation && index >= 0 && index < animations.size())
		{
			currentAnimation = index;
			animations[index]->RestartAnimation();
		}
	}
}

sf::Sprite* Animator::GetCurrentSprite()
{
	return animations[currentAnimation]->GetCurrentAnimationFrame();
}

Animation* Animator::GetAnimationByName(std::string name)
{
	if (animations.empty()) return nullptr;
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations[i]->GetName() == name)
		{
			return animations[i];
		}
	}
}

int Animator::GetAnimationByIndex(std::string name)
{
	if (animations.empty()) return -1;
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations[i]->GetName() == name)
		{
			return i;
		}
	}
}

void Animator::Flip(bool Flipped)
{
	isFlipped = Flipped;
}
