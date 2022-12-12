#include "Customer.h"

namespace TapperGame {



	Customer::Customer()
	{
	}

	Customer::Customer(sf::Texture& texture, float posX, float posY, float x, float y, float speed)
	{
		rectSourceSprite = sf::IntRect(0, 0, 70, 35);
		customerSprite.setTextureRect(rectSourceSprite);
		customerSprite.setTexture(texture);
		customerSprite.setPosition(posX, posY);
		direction.x = x;
		direction.y = y;
		movementSpeed = speed;

		counterPos.x = posX;
		counterPos.y = posY;
	}

	void Customer::update()
	{
		customerSprite.move(movementSpeed * direction);
	}

	void Customer::render(sf::RenderTarget* target)
	{
		target->draw(customerSprite);
	}

	void Customer::ServeCustomer()
	{
		//have customer go other way
		direction.x = -1.f;
	}

	const sf::FloatRect Customer::getRectBound() const
	{
		return customerSprite.getGlobalBounds();
	}

	const sf::Vector2f& Customer::getCounterPos() const
	{
		return counterPos;
	}

}