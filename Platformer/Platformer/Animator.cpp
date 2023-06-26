#include "Animator.h"
#include <iostream>
#include "Debug.h"
#include "Globals.h"

Animator::Animator(Actor* parentActor)
{
	this->parentActor = parentActor;
	this->type = ComponentType::animator;
	isFlipped = false;
	animations = {};
	animationQ = {};
	currentAnimation = -1;
	animationFPSTarget = 7;
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
		if (currentPlaying != nullptr && (currentPlaying->GetFinishedPlaying() || currentPlaying->GetIsInterupable()))
		{
			if (animationQ.size() > 0)
			{
				std::string name = animationQ[0]->GetName();
				animationQ.erase(animationQ.begin());
				SwitchAnimation(name);
			}
		}
	}
}

void Animator::AddAnimation(Animation* animation)
{
	animations.push_back(animation);
}

void Animator::SwitchAnimation(std::string name)
{
	int index = GetAnimationByIndex(name);
	if (index != currentAnimation && index >= 0 && index < animations.size())
	{
		currentAnimation = index;
		currentPlaying = animations[index];
		currentPlaying->RestartAnimation();
	}
}

void Animator::AddAnimationToQ(Animation* animation)
{
	//dont add same animation again if its first in Q
	if (animationQ.size() > 0)
		if (animationQ[0] == animation) return;
	
	animationQ.push_back(animation);
	if (animationQ.size() == 1)
	{

		SwitchAnimation(animation->GetName());
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
