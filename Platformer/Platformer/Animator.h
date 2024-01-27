#ifndef ANIMATOR_H
#define ANIMATOR_H

#pragma once


#include "Component.h"
#include "SFML/Graphics.hpp"

class Animation;

class Animator : public Component
{
public:
	Animator (Actor* parentActor);
	~Animator();

	virtual void UpdateComponent() override;
	void AddAnimation(Animation* animation);
	void SwitchAnimation(std::string name);
	void AddAnimationToQ(Animation* animation);
	void Flip(bool Flipped);
	sf::Sprite* GetCurrentSprite();
	Animation* GetAnimationByName(std::string name);

private:
	int GetAnimationByIndex(std::string name);

private:
	std::vector<Animation*> animationQ;
	Animation* currentPlaying;
	std::vector<Animation*> animations {};
	sf::Clock clock;
	sf::Time totalElapsed;
	int currentAnimation = 0;
	double animationFPSTarget;
	bool isFlipped;
};
#endif // !ANIMATOR_H