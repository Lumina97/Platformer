#include "ActorRenderer.h"
#include "Collider.h"
#include "Player.h"
#include "Animator.h"

ActorRenderer::ActorRenderer(std::string textureFilePath, sf::RenderWindow* window, Actor* parentActor)
{
	this->parentActor = parentActor;
	setPosition(parentActor->getPosition());
	setOrigin(parentActor->getOrigin());

	this->window = window;
	if (spriteTexture.loadFromFile(textureFilePath) == true)
	{
		sprite.setTexture(spriteTexture);
		sprite.setPosition(getPosition());
	}
}

ActorRenderer::ActorRenderer(sf::Vector2f size, sf::RenderWindow* window, Actor* parentActor)
{
	this->parentActor = parentActor;
	this->window = window;

	setOrigin(parentActor->getOrigin());
	setPosition(parentActor->getPosition());

	shape.setOrigin(getOrigin());
	shape.setSize(sf::Vector2f(size.x - 2, size.y - 2));
}

void ActorRenderer::UpdateComponent()
{
	Component::UpdateComponent();

#ifdef DEBUG=1
	Physics::Collider* col = parentActor->GetComponent < Physics::Collider>();
	sf::FloatRect bounds = col->GetBounds();
	sf::FloatRect current = col->GetBounds();

	debug.setOrigin(getOrigin());
	debug.setSize(sf::Vector2f(bounds.width, bounds.height));
	debug.setPosition(getPosition());

	Player* player = dynamic_cast<Player*>(parentActor);
	if (player != nullptr)
	{
		debug.setFillColor(sf::Color::Transparent);

		sf::RectangleShape spriteDebug;
		Animator* anim = player->GetComponent<Animator>();
		sf::Sprite sprite = *anim->GetCurrentSprite();

		sf::Vector2f origin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height);
		spriteDebug.setScale(2.0f, 2.0f);
		spriteDebug.setOrigin(origin);
		spriteDebug.setPosition(getPosition());
		sf::Vector2f size(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
		spriteDebug.setSize(size);
		spriteDebug.setFillColor(sf::Color::Transparent);
		spriteDebug.setOutlineColor(sf::Color::White);
		spriteDebug.setOutlineThickness(0.5f);

		window->draw(spriteDebug);


	}
	else 
		debug.setFillColor(sf::Color::Red);
	debug.setOutlineThickness(2);
	debug.setOutlineColor(sf::Color::Green);

#endif

	//shape.setFillColor(sf::Color::Transparent);
	//shape.setOutlineThickness(2);
	//shape.setOutlineColor(sf::Color::White);
	//
	//
	//shape.setPosition(getPosition());
	//shape.setOrigin(getOrigin());
	//shape.setRotation(getRotation());

	if (window)
	{
		//window->draw(shape);
		window->draw(debug);
	}
}

