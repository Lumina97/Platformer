#include "Animation.h"
#include <iostream>


Animation::Animation(std::string name, sf::Texture* spriteAtlas, sf::IntRect spriteSize, int length, int rows, int columns, int rowStart, int columnStart)
{
	this->name = name;
	this->spriteAtlas = spriteAtlas;
	this->spriteSize = spriteSize;
	this->length = length;
	this->rows = rows;
	this->columns = columns;
	this->columnStart = columnStart;
	this->rowStart = rowStart;


	if (spriteAtlas == nullptr) {
		std::cout << "Texture was nullptr\n";
		return;
	}

	int x = columnStart;
	int y = rowStart;
	sf::IntRect position = spriteSize;

	for (int i = 0; i < length; i++)
	{
		//load sprite and set texture area
		sf::Sprite* sprite = new sf::Sprite();
		sprite->setTexture(*spriteAtlas);
		position.left = x * position.width;
		position.top = y * position.height;
		sprite->setTextureRect(position);

		sprites.push_back(sprite);

		if (++x >= columns)
		{
			x = 0;
			if (++y >= rows)
			{
				y++;
			}
		}
	}
}

sf::Sprite* Animation::GetCurrentAnimationFrame()
{
	return sprites[currentFrame];
}

void Animation::UpdateAnimation()
{	
	currentFrame++;
	if (currentFrame >= length)
		currentFrame = 0;
}

void Animation::RestartAnimation()
{
	currentFrame = 0;
}

std::string Animation::GetName()
{
	return name;
}
