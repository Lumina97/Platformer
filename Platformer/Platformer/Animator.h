#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "Component.h"
#include "Animation.h"
#include "SFML/Graphics.hpp"

struct AnimationTransitions
{
	Animation* fromAnimation;
	Animation* toAnimation;
	bool finishAnimationBeforeSwitching;
	bool setNewToAnimation;
};

class Animator : public Component
{
public:
	Animator (Actor* parentActor);
	~Animator();

	virtual void UpdateComponent() override;
	void AddAnimation(Animation* animation);
	void SwitchAnimation(std::string name, AnimationTransitions transition = {} );
	void Flip(bool Flipped);
	sf::Sprite* GetCurrentSprite();
	Animation* GetAnimationByName(std::string name);


private:
	int GetAnimationByIndex(std::string name);

private:
	AnimationTransitions lastTransition;
	std::vector<Animation*> animations {};
	sf::Clock clock;
	sf::Time totalElapsed;
	int currentAnimation = 0;
	const double animationFPSTarget = 5;
	bool isFlipped;
};
#endif // !ANIMATOR_H