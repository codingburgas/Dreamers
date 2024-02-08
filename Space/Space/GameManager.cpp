#include "GameManager.h"

GameManager* GameManager::sInstance = NULL;

GameManager* GameManager::Instance()
{
	// Create a new instance if it doesn't exist
	if (sInstance == NULL)
	{
		sInstance = new GameManager();
		return sInstance;
	}
}

void GameManager::Release() {
	delete sInstance;
	sInstance = NULL;
}

// Constructor
GameManager::GameManager()
{
	mQuit = false;
	mGraphics = GameGraphics::Instance(); // Obtain a singleton instance of the GameGraphics class for rendering

	// Check if GameGraphics initialization failed
	if (!GameGraphics::Initialized()) {
		mQuit = true;
	}
}

// Destructor
GameManager::~GameManager()
{
	// Destructor releases resources, including calling the finction
	GameGraphics::Release();
	mGraphics = NULL;
}

void GameManager::Run() {
	// Continue the game  
	while (!mQuit)
	{
		// Continuously check and handle SDL events
		while (SDL_PollEvent(&mEvents) != 0)
		{
			// Check if the SDL event type is a request to quit the game
			if (mEvents.type == SDL_QUIT)
			{
				mQuit = true; 
			}
			mGraphics->Render(); // Render graphics
		}
	}
}


