#pragma once
#include <vector>
#include "Drink.h"
#include "Customer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
/*
The customer manager instatiates customer objects 
as well as managing the randomized spawning system and increasing difficulty

*/

namespace TapperGame 
{
	class CustomerManager
	{
	private:
		//std::vector<Drink>& spawnedDrinks;
		//std::vector<sf::Vector2f>& spawnPositions;
		sf::Texture customerTextures;


		std::vector<Customer> spawnedCustomers;
		std::vector<sf::Vector2f>* spawnPositions;
		std::vector<Drink>* spawnedDrinks;

		float customerSpeed = 1.f;
		float spawnRate = 5.f;
		sf::Clock clock;

		void SpawnSystem();
		void CheckCollisions();

	public:


		CustomerManager();
		~CustomerManager();

		void Reset();

		void initialize(std::vector<Drink>* drinksRef, std::vector<sf::Vector2f>* spawnPositionsRef);

		void update();
		void render(sf::RenderTarget* target);

		const std::vector<Customer>& getCustomers() const;

	};

}

