#include "Player.h"
#include <iostream>
namespace TapperGame {
	void Player::initVariables()
	{
		texture.loadFromFile("assets/BartenderSpriteSheet.png");
		drinkTexture.loadFromFile("assets/DrinkSpriteSheet.png");
		rectSourceSprite =sf::IntRect(0, 0, 35, 90);
		sprite = sf::Sprite(texture, rectSourceSprite);
		sprite.scale(1.2f, 1.2f);

	}
	Player::Player(float x, float y)
	{
		initVariables();
		sprite.setPosition(x, y);
	}

	void Player::ServeDrink()
	{
		drinks.push_back(Drink(drinkTexture, getPos().x-30, getPos().y+15, -1.f, 0.f, 1.f, counterPositions->at(currentCounter)));
		pourStarted = false;
		pouredAmount = 0.f;
	}

	void Player::UpdateDrinks()
	{
		// update position, animation, and autodestroy drinks out of frame
		std::int16_t counter = 0;
		for (auto& drink : drinks)
		{
			drink.update(clock);

			if (drink.getRectBound().left + drink.getRectBound().width > 1280.f) 
			{
				drinks.erase(drinks.begin() + counter);
			}
			++counter;
		}

	}

	void Player::update()
	{
		checkInput();
		UpdateDrinks();

		if (moving == false) 
		{
			if (pouringDrink)  //Pouring Animation : pouring & finishedPouring
			{
				rectSourceSprite.top = 0;
				rectSourceSprite.width = 69;
				if (pouredAmount >= pouredAmountNeeded) {
					rectSourceSprite.left = 165;
				}
				else
				{
					rectSourceSprite.left = 100;
				}

				sprite.setTextureRect(rectSourceSprite);
				pourStarted = true;
				pouredAmount += .1f;
			}
			else
			{
				if (pourStarted && pouredAmount > pouredAmountNeeded) 
				{
					ServeDrink();
				}

				//Idle Animations
				rectSourceSprite.top = 0;
				rectSourceSprite.width = 35;
				if (clock.getElapsedTime().asSeconds() > .5f) 
				{
					if (rectSourceSprite.left == 35)
						rectSourceSprite.left = 0;
					else
						rectSourceSprite.left = 35;

					sprite.setTextureRect(rectSourceSprite);
					clock.restart();
				}
			}

		}
		else if(moving)//Moving Animation
		{
			pouredAmount = 0.f;

			rectSourceSprite.left = 0;
			rectSourceSprite.width = 35;
			rectSourceSprite.top = 100;
			sprite.setTextureRect(rectSourceSprite);
		}
	}

	void Player::checkInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			moving = true;
		}
		else {
			moving = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			pouringDrink = true;
		}
		else {
			pouringDrink = false;
		}
	}

	void Player::render(sf::RenderTarget* target)
	{
		target->draw(sprite);

	}

	const sf::Vector2f& Player::getPos()
	{
		return sprite.getPosition();
	}

	void Player::MoveUp()
	{
		if (currentCounter != 0) 
		{
			--currentCounter;
			moving = true;
		}
		sf::Vector2f curCounter = counterPositions->at(currentCounter);
		sprite.setPosition(curCounter.x + curCounter.y + 420 , counterPositions->at(currentCounter).y-20);
	}

	void Player::MoveDown()
	{
		if (currentCounter != counterPositions->size()-1)
		{
			++currentCounter;
			moving = true;
		}
		sf::Vector2f curCounter = counterPositions->at(currentCounter);
		sprite.setPosition(curCounter.x + curCounter.y + 420, counterPositions->at(currentCounter).y - 20);

//		sprite.setPosition(920.f, counterPositions->at(currentCounter).y-10);
	}
	const sf::FloatRect Player::getRectBound() const
	{
		return sprite.getGlobalBounds();
	}
}