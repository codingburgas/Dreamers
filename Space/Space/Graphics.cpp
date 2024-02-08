#include "Graphics.h"

GameGraphics* GameGraphics::singletonInstance = NULL;
bool GameGraphics::singletonInitialized = false;

GameGraphics* GameGraphics::Instance()
{
	if (singletonInstance == NULL)
	{
		singletonInstance = new GameGraphics(); // Create a new GameGraphics instance and assing it to singletonInstance
		return singletonInstance;
	}
}

void GameGraphics::Release()
{
	delete singletonInstance;
	singletonInstance = NULL;

	singletonInitialized = false;
}

// Check if GameGraphics has been initialized
bool GameGraphics::Initialized()
{
	return Initialized;
}

GameGraphics::GameGraphics() {
	mainBackBuffer = NULL;
	singletonInitialized = Init(); // Initialize the signleton instance and update the initialization status
}
GameGraphics::~GameGraphics()
{
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	SDL_Quit();
}

// Initialize SDL and create the main window
bool GameGraphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	mainWindow = SDL_CreateWindow("Dreamers Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	
	// Check if window creation was succesful
	if (mainWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	mainBackBuffer = SDL_GetWindowSurface(mainWindow); // Obtain the surface of the main window and assign it to mainBackBuffer
	return true;
}

// Update the window surface
void GameGraphics::Render()
{
	SDL_UpdateWindowSurface(mainWindow);
}