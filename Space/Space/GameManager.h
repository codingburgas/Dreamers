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

public:

	static GameManager* Instance();
	static void Release();

	void Run(); // Main game loop
	void LoadButtons();
	void LoadLevel();
	void LoadPlanetImage();
	void LoadPlanetTasks();
	void EndGame();
	void LoadInformationTexture();
	void LoadTexture(int stepsPage);

	int stepsPage = 0; // Initialize the pages, used to specify the page or to load the numbers of the pages
	int planetHealth;
	int currentDamage = 0;
	int currentLevel = 0;
	Texture* planet;
private:
	std::vector<Button> buttons;
	TextManager textManager;
	TaskManager taskManager;
	static GameManager* singletonInstance;
	const int FRAME_RATE = 60;
	bool mainQuit;   // Flag to indicate if the game shoul guit
	GameGraphics* mainGraphics; // Responsible for managing graphics and rendering

	AssetManager* mainAssetManager;

	Timer* mTimer;

	SDL_Event mainEvents; // SDL event handler for managing user input and events

	Texture* manageTexture; // Load the Textures from the states

	enum AppState currentState; // Enum variable to track the current state of the application

	GameManager();
	~GameManager();
};
