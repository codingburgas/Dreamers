#pragma once
#include "Texture.h"
#include <iostream>
#include "Timer.h"
#include "Button.h"
#include "AppStates.h"
#include <vector>
#include "TextManager.h"
#include "TaskManager.h"

class GameManager {

private:
	// Container that holds Button objects
	std::vector<Button> buttons;

	TextManager textManager;
	TaskManager taskManager;

	static GameManager* singletonInstance;
	const int FRAME_RATE = 60;

	// Flag to indicate if the game shoul guit
	bool mainQuit;   

	// Responsible for managing graphics and rendering
	GameGraphics* mainGraphics; 

	AssetManager* mainAssetManager;

	Timer* mTimer;
	// SDL event handler for managing user input and events
	SDL_Event mainEvents;
	// Load the Textures from the states
	Texture* manageTexture;
	// Enum variable to track the current state of the application
	enum AppState currentState; 

	GameManager();
	~GameManager();

public:

	static GameManager* Instance();
	static void release();
	// Main game loop
	void run(); 
	// This method is responsible for initializing and loading the buttons in the game.
	void loadButtons();
	// The method includes initializing game elements, setting up obstacles, spawning entities, etc., to prepare the level for gameplay.
	void loadLevel();
	// This method is used to load the image of the planet in the game.
	void loadPlanetImage();
	// This method is responsible for loading and setting up the tasks associated with the planet in the game.
	void loadPlanetTasks();
	// The method is used to handle the actions and clean up tasks when the game ends.
	// Initialize the end window.
	void endGame();
	// Addition information about the planets
	void loadInformationTexture();
	// This method is used to load textures based on the number of pages to be displayed.
	void loadTexture(int stepsPage);

	// Initialize the pages, used to specify the page or to load the numbers of the pages
	int stepsPage = 0; 
	int planetHealth;
	int currentDamage = 0;
	int currentLevel = 0;
	Texture* planet;
};
