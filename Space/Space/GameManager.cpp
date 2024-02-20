#include "GameManager.h"

GameManager* GameManager::singletonInstance = NULL;

GameManager* GameManager::Instance()
{
	// Create a new instance if it doesn't exist
	if (singletonInstance == NULL)
	{
		singletonInstance = new GameManager();
		return singletonInstance;
	}
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
	// Create the buttons area for click events
	Button startButton(61, 163, 182, 70); // Start the game from the main menu
	Button exitButton(274, 274, 182, 71); // Exit the game from the main menu
	Button stepsButton(486, 164, 182, 69); // Go to steps from the mein menu
	Button backButton(22, 22, 39, 26); // Go to previous pages, used in steps pages
	Button nextPageButton(932, 32, 43, 23); // Go to one page ahead, used in steps pages
	Button stageMenuButton(849,24,319,43); // In the last step page, load the main menu
	Button stagePLayButton(792,95,123,183); // In the last step page, play the game
	Button stageExitButton(850,168,122,29); // In the last step page, exit the window

	int stepsPage = 0; // Initialize the pages, used to specify the page or to load the numbers of the pages

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

				// Check if the mouse is over the start button and handle the click
				if (startButton.isMouseOverButton(mousePositionX, mousePositionY) && currentState == STATE_MAIN_MENU) 
				{
					currentState = STATE_GAME;
				}

				// Check if the mouse is over the exit button and handle the click
				if (exitButton.isMouseOverButton(mousePositionX, mousePositionY) && currentState == STATE_MAIN_MENU)
				{
					mainQuit = true; // Exit the main menu
					currentState = STATE_EXIT;
				}

				// Check if the mouse is over the steps button and handle the click
				if (stepsButton.isMouseOverButton(mousePositionX, mousePositionY) && currentState == STATE_MAIN_MENU) 
				{
					currentState = STATE_STEPS;

					// Creating a new Texture object using the constructor with
					manageTexture = new Texture("Steps-Page0.png");
				}

				// Check if the backButton is clicked and the current state is STATE_STEPS
				if (backButton.isMouseOverButton(mousePositionX, mousePositionY) && currentState == STATE_STEPS)
				{
					if (stepsPage == 0)
					{
						currentState = STATE_MAIN_MENU; // Go back to the main menu
						manageTexture = new Texture("Start-Menu.png");
						continue; // Continue to the next iteration of the loop
					}
					// Decrement stepsPage and load the corresponding texture
					stepsPage--;
					LoadTexture(stepsPage); // Or load the previous step page
					continue;
				}

				// Fixes the button and continues until the pages run out
				// Do nothing if on the last page or load the next step page
				if (nextPageButton.isMouseOverButton(mousePositionX, mousePositionY) && currentState == STATE_STEPS)
				{
					// Check if stepsPage is 3
					if (stepsPage == 3)
					{
						continue;
					}
					// Increment stepsPage and load the corresponding texture
					stepsPage++;
					LoadTexture(stepsPage);
					continue;
				}

				// Go back to the main menu if on the last page
				if (stageMenuButton.isMouseOverButton(mousePositionX, mousePositionY) && currentState == STATE_STEPS)
				{
					// Check if stepsPage is 3
					if (stepsPage == 3) 
					{
						// If so, go back to the main menu and set a new texture
						currentState = STATE_MAIN_MENU;
						manageTexture = new Texture("Start-Menu.png");
						continue;
					}
				}

				// Go to the game and start game if on the last page
				if (stagePLayButton.isMouseOverButton(mousePositionX, mousePositionY) && currentState == STATE_STEPS)
				{
					// Check if stepsPage is 3
					if (stepsPage == 3)
					{
						currentState = STATE_GAME;
						continue;
					}
				}

				// Exit the game if on the last page
				if (stageExitButton.isMouseOverButton(mousePositionX, mousePositionY) && currentState == STATE_STEPS)
				{
					// Check if stepsPage is 3
					if (stepsPage == 3)
					{
						mainQuit = true;
						continue;// Give the state to exit the game
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
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				SDL_RenderDrawLine(renderer, 0, 0, 640, 480);
				break;

			// If the game is in the steps state
			case STATE_STEPS:
				manageTexture->Render(); // Render all images from all pages of steps
				break;

			case STATE_EXIT :
				mainQuit = true; // Set the mainQuit flag to true, indicating the program exit
				break;

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


