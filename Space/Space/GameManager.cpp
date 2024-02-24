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

void GameManager::Release() {
	delete singletonInstance;
	singletonInstance = NULL;
}

// Constructor
GameManager::GameManager()
{
	mainQuit = false;
	mainGraphics = GameGraphics::Instance(); // Obtain a singleton instance of the GameGraphics class for rendering
	currentState = STATE_MAIN_MENU;

	// Check if GameGraphics initialization failed
	if (!GameGraphics::Initialized()) {
		mainQuit = true;
	}

	mainAssetManager = AssetManager::Instance();

	mTimer = Timer::Instance();

	manageTexture = new Texture("Start-Menu.png");
}

// Destructor
GameManager::~GameManager()
{
	// Destructor releases resources, including calling the finction
	GameGraphics::Release();
	mainGraphics = NULL;

	AssetManager::Release();
	mainAssetManager = NULL;

	Timer::Release();
	mTimer = NULL;

	delete manageTexture;
	manageTexture = NULL;
}


void GameManager::Run()
{
	LoadButtons();
	// Continue the game  
	while (!mainQuit)
	{
		mTimer->Update();

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

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			mainGraphics->ClearBackBuffer();

			// Use a switch statement to determine the current state of the game
			switch (currentState)
			{
			// If the game is in the main menu state
			case STATE_MAIN_MENU:
				manageTexture->Render(); // Render the textures associated with the main menu
				break;

			// If the game is in the game state
			case STATE_GAME:
				manageTexture->Render();
				break;

			// If the game is in the steps state
			case STATE_STEPS:
				manageTexture->Render(); // Render all images from all pages of steps
				break;

			case STATE_EXIT :
				mainQuit = true; // Set the mainQuit flag to true, indicating the program exit
				break;

			case STATE_GAME_BOOK:
				manageTexture2->Render();

			default:
				break;
			}
			mainGraphics->Render(); // Render graphics
			mTimer->Reset(); // Reset the timer to its initial state
		}
	}
}

void GameManager::LoadTexture(int stepsPage)
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

		//Step-Page 2
	case 2:
		manageTexture = new Texture("Steps-Page2.png");
		break;

		//Step-Page 3
	case 3:
		manageTexture = new Texture("Steps-Page3.png");
		break;
	}
}

void GameManager::LoadButtons()
{
	buttons = std::vector<Button>
	{
		Button(61, 163, 182, 70, STATE_MAIN_MENU, []()
			{
				GameManager* instance = GameManager::Instance();
				instance->currentState = STATE_GAME;
				instance->manageTexture1 = new Texture("Frame 10.png");
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
				instance->LoadTexture(instance->stepsPage); // Or load the previous step page
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
				instance->LoadTexture(instance->stepsPage);
				return true;
			}
		),
		Button(849, 24, 319, 43, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3
				if (instance->stepsPage == 3)
				{
					instance->manageTexture = new Texture("Start-Menu.png");
					instance->currentState = STATE_MAIN_MENU;
					return true;
				}
				return false;
			}
		),
		Button(792, 95, 123, 183, STATE_STEPS, []()
			{
				GameManager* instance = GameManager::Instance();
				// Check if stepsPage is 3
				if (instance->stepsPage == 3)
				{
					instance->currentState = STATE_GAME;
					return true;
				}
				return false;
			}
		),
		Button(850, 168, 122, 29, STATE_STEPS, []()
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
		)
	};
}