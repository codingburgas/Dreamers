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
	mTimer = Timer::Instance();
}

// Destructor
GameManager::~GameManager()
{
	// Destructor releases resources, including calling the finction
	GameGraphics::Release();
	mainGraphics = NULL;

	Timer::Release();
	mTimer = NULL;
}

void GameManager::Run() {
	// Continue the game  
	while (!mainQuit)
	{
		mTimer->Update();

		// Continuously check and handle SDL events
		while (SDL_PollEvent(&mainEvents) != 0)
		{
			// Check if the SDL event type is a request to quit the game
			if (mainEvents.type == SDL_QUIT)
			{
				mainQuit = true; 
			}
		}

		if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE)
		{
			printf("DeltaTime: %F\n", mTimer->DeltaTime()); // Print the elapsed time( delta time) since the last frame in seconds to the console
			mainGraphics->Render(); // Render graphics
			mTimer->Reset(); // Reset the timer to its initial state
		}
	}
}


