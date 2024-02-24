#pragma once
#include "Texture.h"
#include <iostream>
#include "Timer.h"
#include "Button.h"
#include "AppStates.h"
#include <vector>

class GameManager {

public:

	static GameManager* Instance();
	static void Release();

	void Run(); // Main game loop
	std::vector<Button> buttons;
	void LoadButtons();

	void LoadTexture(int stepsPage);
	int stepsPage = 0; // Initialize the pages, used to specify the page or to load the numbers of the pages

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
