#include "Animation.h"
#include <iostream>
#include "Log.h"

Animation::Animation(std::string name, sf::Texture* spriteAtlas, sf::IntRect spriteSize, int length, int rows, int columns, int rowStart, int columnStart, bool interruptable)
{
	this->name = name;
	this->spriteAtlas = spriteAtlas;
	this->spriteSize = spriteSize;
	this->length = length;
	this->rows = rows;
	this->columns = columns;
	this->columnStart = columnStart;
	this->rowStart = rowStart;
	this->interruptable = interruptable;


	if (spriteAtlas == nullptr) {
		 LOG_ERROR("Texture was nullptr");
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

		if (++x - columnStart >= columns)
		{
			x = 0;
			if (++y - rowStart >= rows)
			{
				y++;
			}
		}
	}
}

Animation::~Animation()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->setTexture(sf::Texture());
		delete(sprites[i]);
	}
	sprites.clear();	
}

sf::Sprite* Animation::GetCurrentAnimationFrame()
{
	return sprites[currentFrame];
}

void Animation::UpdateAnimation()
{	
	currentFrame++;
	if (currentFrame >= length)
	{
		hasFinishedPlaying = true;
		currentFrame = 0;
	}
}

void Animation::RestartAnimation()
{
	currentFrame = 0;
	hasFinishedPlaying = false;
}

std::string Animation::GetName()
{
	return name;
}

bool Animation::GetFinishedPlaying()
{
	return hasFinishedPlaying;
}

bool Animation::GetIsInterupable()
{
	return interruptable;
}
