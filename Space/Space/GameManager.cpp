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

	// Check if GameGraphics initialization failed
	if (!GameGraphics::Initialized()) {
		mainQuit = true;
	}

	mainAssetManager = AssetManager::Instance();

	mTimer = Timer::Instance();

	manageTexture = new Texture("Frame 29 (1).png");
	Texture* texture2 = new Texture("Frame 29 (1).png");
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
	Button startButton(61, 163, 182, 70);
	Button exitButton(274, 274, 182, 71);
	Button stepsButton(486, 164, 182, 69);

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
				int mousePositionX, mousePositionY;

				// Get the current mouse coordinates
				SDL_GetMouseState(&mousePositionX, &mousePositionY);

				// Check if the mouse is over the start button and handle the click
				if (startButton.isMouseOverButton(mousePositionX, mousePositionY)) {
					startButton.startGame();
				}

				// Check if the mouse is over the exit button and handle the click
				if (exitButton.isMouseOverButton(mousePositionX, mousePositionY)) {
					exitButton.exitGame();
				}

				// Check if the mouse is over the steps button and handle the click
				if (stepsButton.isMouseOverButton(mousePositionX, mousePositionY)) {
					stepsButton.stepsGame();
				}
			}
			
		}

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			mainGraphics->ClearBackBuffer();
			manageTexture->Render();

			mainGraphics->Render(); // Render graphics
			mTimer->Reset(); // Reset the timer to its initial state
		}
	}
}


