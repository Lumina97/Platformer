#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "Component.h"
#include "Animation.h"
#include "SFML/Graphics.hpp"

class Animator : public Component
{
public:
	Animator(std::vector<Animation*> animations,sf::RenderWindow* window, Actor* parentActor);
	Animator(sf::RenderWindow* window, Actor* parentActor);
	~Animator();

	virtual void UpdateComponent() override;
	void AddAnimation(Animation* animation);
	void SwitchAnimation(std::string name);
	sf::Sprite* GetCurrentSprite();
	void Flip(bool Flipped);

private:
	int currentAnimation = 0;
	std::vector<Animation*> animations {};
	sf::RenderWindow* window;
	const double animationFPSTarget = 5;
	sf::Clock clock;
	sf::Time totalElapsed;
	bool isFlipped;
};
#endif // !ANIMATOR_H