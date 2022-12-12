#include "Drink.h"

namespace TapperGame {


	Drink::Drink(sf::Texture& texture, float posX, float posY, float x, float y, float speed, sf::Vector2f counterPosition)
	{
		rectSourceSprite = sf::IntRect(0, 0, 35, 90);
		drinkSprite.setTextureRect(rectSourceSprite);
		drinkSprite.setTexture(texture);
		drinkSprite.setPosition(posX, posY);
		direction.x = x;
		direction.y = y;
		movementSpeed = speed;

		counterPos.x = counterPosition.x;
		counterPos.y = counterPosition.y;

	}

	void Drink::CustomerDrank()
	{
		drinkSprite.setPosition(2000.f, 0.f); //set to far right to autodestroy
	}

	void Drink::update(sf::Clock &clock)
	{
		drinkSprite.move(movementSpeed * direction);

		//Idle Anim
		rectSourceSprite.top = 0;
		rectSourceSprite.width = 35;
		if (clock.getElapsedTime().asSeconds() > .5f)
		{
			if (rectSourceSprite.left == 35)
				rectSourceSprite.left = 0;
			else
				rectSourceSprite.left = 35;

			drinkSprite.setTextureRect(rectSourceSprite);

		}

	}

	void Drink::render(sf::RenderTarget* target)
	{
		target->draw(drinkSprite);
	}

	const sf::FloatRect Drink::getRectBound() const
	{
		return drinkSprite.getGlobalBounds();
	}

	const sf::Vector2f& Drink::getCounterPos() const
	{
		return counterPos;
	}

}
