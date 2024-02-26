#include "GameManager.h"

GameManager* GameManager::singletonInstance = NULL;

GameManager* GameManager::Instance()
{
	// Create a new instance if it doesn't exist
	if (singletonInstance == NULL)
	{
		singletonInstance = new GameManager();
	}
	return singletonInstance;
}

void GameManager::release() {
	delete singletonInstance;
	singletonInstance = NULL;
}

// Constructor
GameManager::GameManager()
{
	mainQuit = false;
	// Obtain a singleton instance of the GameGraphics class for rendering
	mainGraphics = GameGraphics::Instance(); 
	currentState = STATE_MAIN_MENU;

	// Check if GameGraphics initialization failed
	if (!GameGraphics::initialized()) {
		mainQuit = true;
	}

	mainAssetManager = AssetManager::Instance();

	mTimer = Timer::Instance();

	manageTexture = new Texture("Start-Menu.png");
	taskManager = TaskManager();
	textManager = TextManager(15);
}

// Destructor
GameManager::~GameManager()
{
	// Destructor releases resources, including calling the finction
	GameGraphics::release();
	mainGraphics = NULL;

	AssetManager::release();
	mainAssetManager = NULL;

	Timer::release();
	mTimer = NULL;

	delete manageTexture;
	manageTexture = NULL;
}


void GameManager::run()
{
	loadButtons();
	// Continue the game  
	while (!mainQuit)
	{
		mTimer->update();

		// Continuously check and handle SDL events
		while (SDL_PollEvent(&mainEvents) != 0)
		{
			// Check if the SDL event type is a request to quit the game
			if (mainEvents.type == SDL_QUIT) {
				mainQuit = true;
			}

			if (SDL_MOUSEMOTION == mainEvents.type) {
				int x;
				int y;
				SDL_GetMouseState(&x, &y);
				std::cout << x << " : " << y << std::endl;
			}

			if (SDL_MOUSEBUTTONDOWN == mainEvents.type)
			{
				if (SDL_BUTTON_LEFT == mainEvents.button.button) {
					std::cout << "Left mouse button is down" << std::endl;
				}
				if (SDL_BUTTON_RIGHT == mainEvents.button.button) {
					std::cout << "Right mouse button is down" << std::endl;
				}
			}
			if (SDL_MOUSEBUTTONUP == mainEvents.type)
			{
				if (SDL_BUTTON_LEFT == mainEvents.button.button) {
					std::cout << "Left mouse button is up" << std::endl;
				}
				if (SDL_BUTTON_RIGHT == mainEvents.button.button) {
					std::cout << "Right mouse button is up" << std::endl;
				}
			}
			if (mainEvents.type == SDL_MOUSEBUTTONDOWN)
			{
				// Variables to store the current mouse cursor position on the X-axis and position on the Y-axis
				int mousePositionX, mousePositionY;

				// Get the current mouse coordinates
				SDL_GetMouseState(&mousePositionX, &mousePositionY);

				for (size_t i = 0; i < buttons.size(); i++)
				{
					if (buttons[i].click(mousePositionX, mousePositionY, currentState))
					{
						break;
					}
				}
			}

		}

		if (mTimer->deltaTime() >= (1.0f / FRAME_RATE))
		{
			mainGraphics->clearBackBuffer();

			// Use a switch statement to determine the current state of the game
			switch (currentState)
			{
				// If the game is in the main menu state
			case STATE_GAME_BOOK:
			case STATE_MAIN_MENU:
			case STATE_END:
			case STATE_STEPS:
				manageTexture->render(); // Render the textures associated with the main menu
				break;

				// If the game is in the game state
			case STATE_GAME:
				manageTexture->render();
				planet->renderDestination();
				break;

			case STATE_EXIT:
				// Set the mainQuit flag to true, indicating the program exit
				mainQuit = true;
				break;
			case STATE_TASKS:
				manageTexture->render();
				textManager.render();
				break;
			default:
				break;
			}
			// Render graphics
			mainGraphics->render(); 
			// Reset the timer to its initial state
			mTimer->reset(); 
		}
	}
}

void GameManager::loadTexture(int stepsPage)
{
	// Switch statement to load different textures based on the stepsPage value
	switch (stepsPage)
	{
		// Step-Page 0
	case 0:
		manageTexture = new Texture("Steps-Page0.png");
		break;

		// Step-Page 1
	case 1:
		manageTexture = new Texture("Steps-Page1.png");
		break;

		// Step-Page 2
	case 2:
		manageTexture = new Texture("Steps-Page2.png");
		break;

		// Step-Page 3
	case 3:
		manageTexture = new Texture("Steps-Page3.png");
		break;
	}
}

// It switches between different cases representing different levels to load the corresponding texture image for information display.
void GameManager::loadInformationTexture()
{
	switch (currentLevel)
	{
	case 0:
		manageTexture = new Texture("Venus.png");
		break;
	case 1:
		manageTexture = new Texture("Earth.png");
		break;
	case 2:
		manageTexture = new Texture("Saturn.png");
		break;
	case 3:
		manageTexture = new Texture("Neptune.png");
		break;
	default:
		break;
	}
}

void GameManager::loadPlanetTasks() {
	switch (currentLevel)
	{
	case 0:
		manageTexture = new Texture("Venus-Tasks.png");
		textManager.resetText();
		textManager.addText(taskManager.GetTaskText(currentLevel, 0), 880, 90, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 1), 880, 220, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 2), 880, 360, 100, 70);
		break;
	case 1:
		manageTexture = new Texture("Earth-Tasks.png");
		textManager.resetText();
		textManager.addText(taskManager.GetTaskText(currentLevel, 0), 880, 90, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 1), 880, 220, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 2), 890, 360, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 3), 880, 500, 100, 70);
		break;
	case 2:
		manageTexture = new Texture("Saturn-Tasks.png");
		textManager.resetText();
		textManager.addText(taskManager.GetTaskText(currentLevel, 0), 880, 90, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 1), 880, 220, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 2), 890, 360, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 3), 880, 500, 100, 70);
		break;
	case 3:
		manageTexture = new Texture("Neptune-Tasks.png");
		textManager.resetText();
		textManager.addText(taskManager.GetTaskText(currentLevel, 0), 880, 90, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 1), 880, 220, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 2), 890, 360, 100, 70);
		textManager.addText(taskManager.GetTaskText(currentLevel, 3), 880, 500, 100, 70);
		break;
	}
}



void GameManager::loadButtons()
{
	buttons = std::vector<Button>
	{
		Button(61, 163, 182, 70, STATE_MAIN_MENU, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_GAME;
				instance->loadLevel();
				return true;
			}
		),
		Button(274, 274, 182, 71, STATE_MAIN_MENU, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->mainQuit = true;
				instance->currentState = STATE_EXIT;
				return true;
			}
		),
		Button(486, 164, 182, 69, STATE_MAIN_MENU, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_STEPS;
				instance->manageTexture = new Texture("Steps-Page0.png");
				return true;
			}
		),
		Button(22, 22, 39, 26, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				if (instance->stepsPage == 0)
				{
					instance->currentState = STATE_MAIN_MENU; // Go back to the main menu
					instance->manageTexture = new Texture("Start-Menu.png");
					return true; // Continue to the next iteration of the loop
				}
				// Decrement stepsPage and load the corresponding texture
				instance->stepsPage--;
				instance->loadTexture(instance->stepsPage); // Or load the previous step page
				return true;
			}
		),
		Button(932, 32, 43, 23, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3
				if (instance->stepsPage == 3)
				{
					return false;
				}
				// Increment stepsPage and load the corresponding texture
				instance->stepsPage++;
				instance->loadTexture(instance->stepsPage);
				return true;
			}
		),
		Button(849, 24, 319, 43, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3
				if (instance->stepsPage == 3)
				{
					instance->stepsPage = 0;
					instance->manageTexture = new Texture("Start-Menu.png");
					instance->currentState = STATE_MAIN_MENU;
					return true;
				}
				return false;
			}
		),
		Button(790, 110, 110, 30, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3
				if (instance->stepsPage == 3)
				{
					instance->loadLevel();
					instance->stepsPage = 0;
					instance->currentState = STATE_GAME;
					return true;
				}
				return false;
			}
		),
		Button(849, 173, 129, 30, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3
				if (instance->stepsPage == 3)
				{
					instance->mainQuit = true;
					return true;
				}
				return false;
			}
		),


		Button(350, 180, 350, 350, STATE_GAME, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentDamage++;
				if (instance->planetHealth + 1 == instance->currentDamage)
				{
					instance->currentLevel++;
					instance->currentDamage = 0;
					if (instance->currentLevel == 4)
					{
						instance->endGame();
					}
					else
					{
						instance->loadLevel();
					}
					return true;
				}
				else
				{
					instance->loadPlanetImage();
				}
				instance->taskManager.evaluateScore(instance->currentLevel);
				return true;
			}
		),

		Button(849, 24, 319, 43, STATE_GAME, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3
				if (instance->stepsPage == 1)
				{
					instance->stepsPage = 0;
					instance->manageTexture = new Texture("Start-Menu.png");
					instance->currentState = STATE_MAIN_MENU;
					return true;
				}
				return false;
			}
		),

		Button(730, 500, 110, 100, STATE_GAME, []()
			{
				GameManager* instance = GameManager::Instance();

				instance->currentState = STATE_GAME_BOOK;
				instance->loadInformationTexture();
				return true;
			}
		),

		Button(870, 500, 110, 100, STATE_GAME, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_TASKS;
				instance->loadPlanetTasks();
				return true;
			}
		),

		Button(22, 22, 39, 26, STATE_GAME_BOOK, []()
			{
				GameManager* instance = GameManager::Instance();

				instance->currentState = STATE_GAME;
				instance->loadPlanetImage();
				instance->manageTexture = new Texture("level-" + std::to_string(instance->currentLevel) + ".png");

				return true;
			}
		),

		Button(22, 22, 39, 26, STATE_TASKS, []()
		{
			GameManager* instance = GameManager::Instance();
			instance->currentState = STATE_GAME;
			instance->loadPlanetImage();
			instance->manageTexture = new Texture("level-" + std::to_string(instance->currentLevel) + ".png");
			return true;
			}
		),

		Button(686, 37, 120, 25, STATE_GAME, []()
		{
			GameManager* instance = GameManager::Instance();
			instance->currentState = STATE_MAIN_MENU;
			instance->manageTexture = new Texture("Start-Menu.png");
			return true;
			}
		), 

		Button(840, 35, 115, 25, STATE_GAME, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_EXIT;
				return true;
			}
		),

		Button(188, 143, 157, 37, STATE_END, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_MAIN_MENU;
				instance->setTexture("Start-Menu.png");
				return true;
			}
		),

		Button(305, 251, 151, 29, STATE_END, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_EXIT;
				return true;
			}
		),
	};
}

void GameManager::loadLevel()
{
	loadPlanetImage();
	manageTexture = new Texture("level-" + std::to_string(currentLevel) + ".png");

	switch (currentLevel)
	{
		// Venus
	case 0:
		planetHealth = 2;
		break;
		// Earth
	case 1:
		planetHealth = 2;
		break;
		// Saturn
	case 2:
		planetHealth = 3;
		break;
		// Neptune
	case 3:
		planetHealth = 3;

	default:
		break;
	}
}

void GameManager::loadPlanetImage()
{
	std::string planetName = "planeta" + std::to_string(currentLevel) + "-" + std::to_string(currentDamage) + ".png";
	planet = new Texture(planetName, 300, 180, 400, 350);
}

void GameManager::endGame()
{
	currentState = STATE_END;
	currentLevel = 0;
	currentDamage = 0;
	manageTexture = new Texture("End-Game.png");
}


void GameManager::setTexture(std::string path)
{
	manageTexture = new Texture(path);
}
