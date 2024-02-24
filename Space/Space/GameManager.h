#pragma once
#include "Texture.h"
#include <iostream>
#include "Timer.h"
#include "Button.h"
#include "AppStates.h"

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
	Texture* manageTexture1;
	Texture* manageTexture2;

	SDL_Renderer* renderer;
	enum AppState currentState; // Enum variable to track the current state of the application

	GameManager();
	~GameManager();
};
