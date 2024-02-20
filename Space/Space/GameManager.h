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

	void LoadTexture(int stepsPage);

private:

	static GameManager* singletonInstance;
	const int FRAME_RATE = 120;

	bool mainQuit;   // Flag to indicate if the game shoul guit
	GameGraphics* mainGraphics; // Responsible for managing graphics and rendering

	AssetManager* mainAssetManager;

	Timer* mTimer;

	SDL_Event mainEvents; // SDL event handler for managing user input and events

	Texture* manageTexture; // Load the Textures from the states

	SDL_Renderer* renderer;
	enum AppState currentState; // Enum variable to track the current state of the application

	GameManager();
	~GameManager();
};

// Enumeration representing different states of the game
enum AppState {
	STATE_MAIN_MENU, // State to take us to the main menu
	STATE_GAME, // State to take is to ply game
	STATE_STEPS, // State to take us to the steps pages
	STATE_EXIT // State to exit the game
};