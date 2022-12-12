#include "CustomerManager.h"

namespace TapperGame {


	CustomerManager::CustomerManager()
	{
		customerTextures.loadFromFile("assets/CustomerSpriteSheet.png");
		spawnPositions = nullptr;
		spawnedDrinks = nullptr;
	}

	void CustomerManager::SpawnSystem()
	{
		if (clock.getElapsedTime().asSeconds() > spawnRate) {

			std::size_t randomPos = (rand() % spawnPositions->size());

			sf::Vector2f randomSpawn = spawnPositions->at(randomPos);
			spawnedCustomers.push_back(Customer(customerTextures, randomSpawn.x, randomSpawn.y, 1.f, 0.f, customerSpeed ));

			if (spawnRate > .3f)
			{
				spawnRate -= .1f;
			}
			customerSpeed += .1f;
			clock.restart();
		}
	}

	void CustomerManager::CheckCollisions()
	{
		std::int16_t counter = 0;
		//Check each customer against spawnedDrinks if collision we will have customer go otherway
		for (auto& customer : spawnedCustomers)
		{
			for (auto& drink : *spawnedDrinks)
			{
				if (customer.getRectBound().intersects(drink.getRectBound()))
				{
					customer.ServeCustomer();
					drink.CustomerDrank();

				}
			}
		}

	}

	void CustomerManager::initialize(std::vector<Drink>* drinksRef, std::vector<sf::Vector2f>* spawnPositionsRef) {

		spawnedDrinks = drinksRef;
		spawnPositions = spawnPositionsRef;

	}

	void CustomerManager::update()
	{
		// update customers, autodestroy, check collisions, and spawn new customers
		std::int16_t counter = 0;
		for (auto& customer : spawnedCustomers)
		{
			customer.update();

			if (customer.getRectBound().left + customer.getRectBound().width < customer.getCounterPos().x) {
				spawnedCustomers.erase(spawnedCustomers.begin() + counter); 
			}
			++counter;
		}

		SpawnSystem();
		CheckCollisions();
	}

	void CustomerManager::render(sf::RenderTarget* target)
	{
		for (auto& customer : spawnedCustomers)
		{
			customer.render(target);
		}
	}

	const std::vector<Customer>& CustomerManager::getCustomers() const
	{
		return spawnedCustomers;
	}

	CustomerManager::~CustomerManager()
	{
		//delete spawnedDrinks;
		//delete spawnPositions;
	}

	void CustomerManager::Reset()
	{
		spawnedCustomers.clear();
		customerSpeed = 1.f;
		spawnRate = 5.f;

		spawnedDrinks->clear();
	}


}

