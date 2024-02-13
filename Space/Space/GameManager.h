#pragma once
#include "Graphics.h"
#include <iostream>
#include "Timer.h"
#include "GameEntity.h"

class GameManager {

public:

	static GameManager* Instance();
	static void Release();

	void Run(); // Main game loop

private:

	static GameManager* singletonInstance;
	const int FRAME_RATE = 120;

	bool mainQuit;   // Flag to indicate if the game shoul guit
	GameGraphics* mainGraphics; // Responsible for managing graphics and rendering

	Timer* mTimer;

	SDL_Event mainEvents; // SDL event handler for managing user input and events

	GameManager();
	~GameManager();
};