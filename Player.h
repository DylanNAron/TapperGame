#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Drink.h"
/*
The Player class is the bartender
we can move up / down the counters with arrow keys
and we can pour drinks with space button

Player class handles input/player action as well as spawning of drink objects

*/

namespace TapperGame {

	class Player
	{
	private:
		sf::IntRect rectSourceSprite;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Clock clock;

		sf::Texture drinkTexture;


		std::int16_t currentCounter = 0;

		float pouredAmount = 0.f;
		float pouredAmountNeeded = 3.f;
		bool moving = false;
		bool pouringDrink = false;
		bool pourStarted = false;

		void initVariables();
		void ServeDrink();
		void UpdateDrinks();
	public:
		std::vector<Drink> drinks;
		std::vector<sf::Vector2f>* counterPositions;
		Player(float x = 850.f, float y = 120.f);

		void update();
		void checkInput();
		void render(sf::RenderTarget *target);

		const sf::Vector2f& getPos();

		void MoveUp();
		void MoveDown();

		const sf::FloatRect getRectBound() const;

	};

}

