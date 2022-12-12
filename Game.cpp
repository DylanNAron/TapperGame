#include "Game.h"

namespace TapperGame {

	void Game::initVariables()
	{
		window = nullptr;
		player.counterPositions = &counterPositions;
		//Create the bar 
		//Counter positions used for spawning/movment (can add more/less and edit their positions!)
		counterPositions.push_back(sf::Vector2f(290.f, 140.f));
		counterPositions.push_back(sf::Vector2f(230.f, 280.f));
		counterPositions.push_back(sf::Vector2f(160.f, 430.f));
		counterPositions.push_back(sf::Vector2f(100.f, 570.f));
		
		//initialize shapes for counters in game background (for debugging)
		for (sf::Vector2f counterPos : counterPositions) {

			sf::RectangleShape counter(sf::Vector2f(baseCounterWidth+counterPos.y, counterHeight));
			counter.setFillColor(sf::Color(150,75,0,255));
			counter.setPosition(counterPos.x, counterPos.y+31);
			counters.push_back(counter);

		}
		
		//Initialize the spawning
		customerManager.initialize(&player.drinks, &counterPositions);

		//Text
		font.loadFromFile("assets/pixelmix.ttf");
		gameOverText.setFont(font);
		gameOverText.setString("GAME OVER! \npress Enter\nto restart");
		gameOverText.setCharacterSize(80);
		gameOverText.setPosition(350 , 300);

		//Background
		backgroundTex.loadFromFile("assets/Background.png");
		background.setTexture(backgroundTex);

		//MainMenu
		mainMenuTexture.loadFromFile("assets/MainMenu.png");
		mainMenu.setTexture(mainMenuTexture);
		mainMenuRect.width = 640;
		mainMenuRect.height = 360;
		mainMenuRect.left = 0;
		mainMenu.setTextureRect(mainMenuRect);
		mainMenu.scale(2.f,2.f);

	}

	void Game::initWindow()
	{
		this->videoMode.height = 720;
		this->videoMode.width = 1280;
		this->window = new sf::RenderWindow(videoMode, "Dylan's Tapper Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

		window->setFramerateLimit(60);
	}

	void Game::UpdateGameState()
	{
		for (auto& customer : customerManager.getCustomers())
		{
			if (customer.getRectBound().left + customer.getRectBound().width > baseCounterWidth + customer.getCounterPos().y + customer.getCounterPos().x )
			{
				//If a customer reaches the end of a counter we lose
				isGameOver = true;

			}

		}

		for (auto& drink : player.drinks)
		{
			if (drink.getRectBound().left < drink.getCounterPos().x )
			{
				isGameOver = true;
			}
		}
	}

	void Game::ResetGame()
	{

		customerManager.Reset();
		isMainMenu = true;
		isGameOver = false;

	}

	Game::Game()
	{
		this->initVariables();
		this->initWindow();
	}

	Game::~Game()
	{
		delete this->window;
	}

	const bool Game::isRunning() const
	{
		return this->window->isOpen();
	}

	void Game::pollEvents()
	{
		//eventpolling
		while (this->window->pollEvent(this->event))
		{
			switch (this->event.type)
			{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window->close();
				if (this->event.key.code == sf::Keyboard::Up)
					player.MoveUp();
				if (this->event.key.code == sf::Keyboard::Down)
					player.MoveDown();
				if (isMainMenu && this->event.key.code == sf::Keyboard::Enter)
					isMainMenu = false;
				if (isGameOver && this->event.key.code == sf::Keyboard::Enter)
					ResetGame();
				break;
			}
		}
	}

	void Game::update()
	{
		this->pollEvents();
		if (!isGameOver && !isMainMenu) 
		{
			player.update();
			customerManager.update();
			UpdateGameState();
		}
		else if (isMainMenu)
		{
			UpdateMainMenu();
		}

	}

	void Game::render()
	{
		window->clear(sf::Color(181, 101, 29, 255));

		if (isMainMenu)
		{
			window->draw(mainMenu);
			//window->draw(titleText);
		}
		else
		{

			window->draw(background);

			/* Debugging for counter positions image
			for (auto& counter : counters)
			{
				window->draw(counter);
			}*/

			player.render(window);

			for (auto& drink : player.drinks)
			{
				drink.render(window);
			}

			customerManager.render(window);

			if (isGameOver)
			{
				window->draw(gameOverText);
			}
		}



		window->display();
	}

	void Game::UpdateMainMenu()
	{
		if (mainMenuClock.getElapsedTime().asSeconds() > .5f)
		{
			if (mainMenuRect.left == 0)
				mainMenuRect.left = 640;
			else if(mainMenuRect.left == 640)
				mainMenuRect.left = 1280;
			else if (mainMenuRect.left == 640)
				mainMenuRect.left = 1280;
			else if (mainMenuRect.left == 1280)
				mainMenuRect.left = 1920;
			else if (mainMenuRect.left == 1920)
				mainMenuRect.left = 2560;
			else if (mainMenuRect.left == 2560)
				mainMenuRect.left = 0;

			mainMenu.setTextureRect(mainMenuRect);
			mainMenuClock.restart();
		}
	}

}


