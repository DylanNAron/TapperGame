#include <iostream>
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
* Tapper Game in C++ using SFML by Dylan Aron
* Created 12/6/22
* 
* The updating is handled in the Game class
* which then instatiates our CustomerManager and Player objects to interact with the world
* customer objects are spawned randomly and the player can serve drink objects as well as navigate the counters within the bar
* 
* Hit Enter to Start 
* up/down key to move up and down
* Press and Hold spacebar to fill and serve a drink
* 
*/



int main()
{

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	//Init the engine
	TapperGame::Game game;


	//GAME loop
	while (game.isRunning())
	{
		game.update();
		game.render();
	}

	return 0;

}