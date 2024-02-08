#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "Graphics.h"
#include <iostream>

class GameManager {

private:

	static GameManager* singletonInstance;
	bool mainQuit;   // Flag to indicate if the game shoul guit
	GameGraphics* mainGraphics; // Responsible for managing graphics and rendering

	SDL_Event mainEvents; // SDL event handler for managing user input and events

	GameManager();
	~GameManager();

public:

	static GameManager* Instance();
	static void Release();

	void Run(); // Main game loop

};

#endif