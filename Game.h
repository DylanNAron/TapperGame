#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Player.h"
#include "Drink.h"
#include "Customer.h"
#include "CustomerManager.h"

/*
Game class 
that instatiates our bar level and the objects needed
this class handles the updating and rendering of our objects
as well as checking our game state if we lose
*/

namespace TapperGame {

	class Game
	{
	private:

		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event event;

		sf::Texture backgroundTex;
		sf::Sprite background;

		sf::Clock mainMenuClock;
		sf::Texture mainMenuTexture;
		sf::Sprite mainMenu;
		sf::IntRect mainMenuRect;

		float baseCounterWidth = 400.f; //to create different counter widths we take this base counter size and add the y value to stretch is based on depth
		float counterHeight = 50.f;
		std::vector<sf::Vector2f> counterPositions; //spawn positions for customers
		std::vector<sf::RectangleShape> counters;

		sf::Font font;
		sf::Text gameOverText;


		Player player;
		CustomerManager customerManager;

		bool isGameOver = false;
		bool isMainMenu = true;

		void initVariables();
		void initWindow();

		void UpdateGameState();

		void ResetGame();
		void UpdateMainMenu();

	public:
		Game();
		~Game();

		const bool isRunning() const;

		void pollEvents();
		void update();
		void render();
	};
}
