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
	// Initialize a TaskManager object for managing tasks.
	taskManager = TaskManager();
	// Initialize a TextManager object with a font size of 15 for managing text rendering.
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
	// Continue the game.
	while (!mainQuit)
	{
		mTimer->update();

		// Continuously check and handle SDL events.
		while (SDL_PollEvent(&mainEvents) != 0)
		{
			// Check if the SDL event type is a request to quit the game.
			if (mainEvents.type == SDL_QUIT) {
				mainQuit = true;
			}
			// Check if the SDL event type is mouse motion.
			if (SDL_MOUSEMOTION == mainEvents.type) {
				int x;
				int y;
				SDL_GetMouseState(&x, &y);
				// Print the mouse coordinates.
				std::cout << x << " : " << y << std::endl;
			}

			// Check if the SDL event type is mouse button down.
			if (SDL_MOUSEBUTTONDOWN == mainEvents.type)
			{
				// Check if the left mouse button is down.
				if (SDL_BUTTON_LEFT == mainEvents.button.button) {
					std::cout << "Left mouse button is down" << std::endl;
				}
				// Check if the right mouse button is down.
				if (SDL_BUTTON_RIGHT == mainEvents.button.button) {
					std::cout << "Right mouse button is down" << std::endl;
				}
			}
			// Check if the SDL event type is mouse button up.
			if (SDL_MOUSEBUTTONUP == mainEvents.type)
			{
				// Check if the left mouse button is up.
				if (SDL_BUTTON_LEFT == mainEvents.button.button) {
					std::cout << "Left mouse button is up" << std::endl;
				}
				// Check if the right mouse button is up.
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

// It switches between different cases representing different levels to load the corresponding tasks, task texts, and task positions for each planet.
// This method helps in defining mission objectives, challenges, or quests related to each planet that players need to complete during gameplay.
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
		// Start game from the main menu.
		Button(61, 163, 182, 70, STATE_MAIN_MENU, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_GAME;
				instance->loadLevel();
				return true;
			}
		),
		// Exit button from the main menu.
		Button(274, 274, 182, 71, STATE_MAIN_MENU, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->mainQuit = true;
				instance->currentState = STATE_EXIT;
				return true;
			}
		),
		// Steps pages button from main menu.
		Button(486, 164, 182, 69, STATE_MAIN_MENU, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_STEPS;
				instance->manageTexture = new Texture("Steps-Page0.png");
				return true;
			}
		),
		// Back button go back to the main page from thr Steps-Pages.
		Button(22, 22, 39, 26, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				if (instance->stepsPage == 0)
				{
					// Go back to the main menu
					instance->currentState = STATE_MAIN_MENU; 
					instance->manageTexture = new Texture("Start-Menu.png");
					
					// Continue to the next iteration of the loop.
					return true;
				}
				// Decrement stepsPage and load the corresponding texture.
				instance->stepsPage--;
				// Or load the previous step page.
				instance->loadTexture(instance->stepsPage); 
				return true;
			}
		),

		// Button from the next page of the steps or (go button).
		Button(932, 32, 43, 23, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3
				if (instance->stepsPage == 3)
				{
					return false;
				}
				// Increment stepsPage and load the corresponding texture.
				instance->stepsPage++;
				// Load the corresponding texture for the new stepsPage value.
				instance->loadTexture(instance->stepsPage);
				return true;
			}
		),

		// The button from the third image in Steps-Pages go to the main menu.
		Button(849, 24, 319, 43, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3.
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
		// The button from the third image in Steps-Pages go to the game.
		Button(790, 110, 110, 30, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3.
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
		// Exit button to close the program from Steps-Pages.
		Button(849, 173, 129, 30, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3.
				if (instance->stepsPage == 3)
				{
					instance->mainQuit = true;
					return true;
				}
				return false;
			}
		),
		// The planet click button and the logic for the levels of the planets.
		Button(350, 180, 350, 350, STATE_GAME, []()
			{
				GameManager* instance = GameManager::Instance();
				// Increment the current damage on the planet.
				instance->currentDamage++;

				// Check if the total damage on the planet equals the planet's health.
				if (instance->planetHealth + 1 == instance->currentDamage)
				{
					// Increment the current level.
					instance->currentLevel++;
					// Reset the current damage for the next level.
					instance->currentDamage = 0;
					if (instance->currentLevel == 4)
					{
						// If the maximum level is reached, end the game.
						instance->endGame();
					}
					else
					{
						// Otherwise, load the next level.
						instance->loadLevel();
					}
					// Indicate successful level transition.
					return true;
				}
				else
				{
					// If the planet is not destroyed yet, reload the planet image.
					instance->loadPlanetImage();
				}
				// Evaluate the player's score (for the tasks) based on the current level.
				instance->taskManager.evaluateScore(instance->currentLevel);

				// Return true to indicate successful handling of the damage event.
				return true;
			}
		),
		 // Buttons from the game to go to the main menu in the Step-Pages
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
		// The buttons for the planet information levels
		Button(730, 500, 110, 100, STATE_GAME, []()
			{
				GameManager* instance = GameManager::Instance();

				instance->currentState = STATE_GAME_BOOK;
				instance->loadInformationTexture();
				return true;
			}
		),
		// The buttons for the tasks in the game.
		Button(870, 500, 110, 100, STATE_GAME, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_TASKS;
				instance->loadPlanetTasks();
				return true;
			}
		),
		//	Back buttons from information planets to the game
		Button(22, 22, 39, 26, STATE_GAME_BOOK, []()
			{
				GameManager* instance = GameManager::Instance();

				instance->currentState = STATE_GAME;
				instance->loadPlanetImage();
				// Create a new texture object for the current game level based on the level number.
				instance->manageTexture = new Texture("level-" + std::to_string(instance->currentLevel) + ".png");

				return true;
			}
		),
		// Back buttons from the tasks of the levels to the game.
		Button(22, 22, 39, 26, STATE_TASKS, []()
		{
			GameManager* instance = GameManager::Instance();
			instance->currentState = STATE_GAME;
			instance->loadPlanetImage();
			// Create a new texture object for the current game level based on the level number.
			instance->manageTexture = new Texture("level-" + std::to_string(instance->currentLevel) + ".png");
			return true;
			}
		),
		// The button from the main game to the main menu
		Button(686, 37, 120, 25, STATE_GAME, []()
		{
			GameManager* instance = GameManager::Instance();
			instance->currentState = STATE_MAIN_MENU;
			instance->manageTexture = new Texture("Start-Menu.png");
			return true;
			}
		), 
		// Button in the game to exit the program.
		Button(840, 35, 115, 25, STATE_GAME, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_EXIT;
				return true;
			}
		),
		// Button from the end to go to the main menu.
		Button(188, 143, 157, 37, STATE_END, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_MAIN_MENU;
				instance->setTexture("Start-Menu.png");
				return true;
			}
		),
		// From the last level (end) to exit the program
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
		planetHealth = 20;
		break;
		// Earth
	case 1:
		planetHealth = 25;
		break;
		// Saturn
	case 2:
		planetHealth = 30;
		break;
		// Neptune
	case 3:
		planetHealth = 35;

	default:
		break;
	}
}

// Function to load the image of the planet based on the current level and damage.
void GameManager::loadPlanetImage()
{
	// Generate the name of the planet image using the current level and damage.
	std::string planetName = "planeta" + std::to_string(currentLevel) + "-" + std::to_string(currentDamage) + ".png";
	planet = new Texture(planetName, 300, 180, 400, 350);
}

// Function to end the current game and reset game state and variables
void GameManager::endGame()
{
	currentState = STATE_END;
	// Reset the level and damage variables to 0
	currentLevel = 0;
	currentDamage = 0;
	manageTexture = new Texture("End-Game.png");
}

void GameManager::setTexture(std::string path)
{
	manageTexture = new Texture(path);
}
