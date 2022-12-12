#pragma once

#include <SFML/Graphics.hpp>

/*

Drink objects are spawned by the player and when served to customers cause them to go away
if a drink hits the other side without a customer then it is a broken glass and the player loses

*/

namespace TapperGame
{
	class Drink
	{
	private:
		sf::IntRect rectSourceSprite;
		sf::Sprite drinkSprite;

		sf::Vector2f direction;
		float movementSpeed;

		sf::Vector2f counterPos;

	public:
		//Drink();
		Drink(sf::Texture &texture, float posX, float posY, float x, float y, float speed, sf::Vector2f counterPosition);

		void CustomerDrank();

		void update(sf::Clock& clock);
		void render(sf::RenderTarget* target);

		const sf::FloatRect getRectBound() const;

		const sf::Vector2f& getCounterPos() const;
	};
}