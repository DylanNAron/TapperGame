#pragma once

#include <SFML/Graphics.hpp>

/*
Customer objects are instatiated randomly to go down the bar counters 
and be served by player or cause the player to lose if they reach the end of counter
*/

namespace TapperGame
{


	class Customer
	{
	private:
		sf::IntRect rectSourceSprite;
		sf::Sprite customerSprite;

		sf::Vector2f direction;
		float movementSpeed;

		sf::Vector2f counterPos;

	public:
		Customer();

		Customer(sf::Texture& texture, float posX, float posY, float x, float y, float speed);

		void update();
		void render(sf::RenderTarget* target);

		void ServeCustomer();

		const sf::FloatRect getRectBound() const;

		const sf::Vector2f& getCounterPos() const;
	};



}
