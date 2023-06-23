#ifndef ANIMATION_H
#define ANIMATION_H
#include "SFML/Graphics.hpp"

class Animation
{
public:
	Animation(std::string name, sf::Texture* spriteAtlas, sf::IntRect spriteSize, int length, int rows, int coloumns,int rowStart, int columnStart);
	~Animation();
	sf::Sprite* GetCurrentAnimationFrame();
	void UpdateAnimation();
	void RestartAnimation();
	std::string GetName();

private:
	std::string name;
	sf::IntRect spriteSize;
	sf::Texture* spriteAtlas;
	int length;
	int rows;
	int columns;
	int columnStart;
	int rowStart;

	int currentFrame;

	std::vector<sf::Sprite*> sprites {};
};


#endif // !ANIMATION_H