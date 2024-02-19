#pragma once
#include "Texture.h"
#include <iostream>
#include "Timer.h"
#include "Button.h"



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

	AssetManager* mainAssetManager;

	Timer* mTimer;

	SDL_Event mainEvents; // SDL event handler for managing user input and events

	Texture* manageTexture;

	Texture* manageTexture2; // Used for displaying image in steps state
	SDL_Texture* texture3;

	Texture* manageTexture4;
	SDL_Texture* texture4;

	Texture* managerTexture5;
	SDL_Texture* texture5;

	SDL_Renderer* renderer;
	enum AppState currentState;

	GameManager();
	~GameManager();
};

// Enumeration representing different states of the game
enum AppState {
	STATE_MAIN_MENU,
	STATE_GAME,
	STATE_STEPS,
	STATE_EXIT,
	STATE_STEPS1,
	STATE_STEPS2,
	STATE_STEPS3
};