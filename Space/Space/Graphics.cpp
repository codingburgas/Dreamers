#include "Graphics.h"

GameGraphics* GameGraphics::singletonInstance = NULL;
bool GameGraphics::singletonInitialized = false;

GameGraphics* GameGraphics::Instance()
{
	if (singletonInstance == NULL)
	{
		singletonInstance = new GameGraphics();
		return singletonInstance;
	}
}

void GameGraphics::Release()
{
	delete singletonInstance;
	singletonInstance = NULL;

	singletonInitialized = false;
}
bool GameGraphics::Initialized()
{
	return Initialized;
}

GameGraphics::GameGraphics() {
	mainBackBuffer = NULL;
	singletonInitialized = Init();
}
GameGraphics::~GameGraphics()
{
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	SDL_Quit();
}

bool GameGraphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	mainWindow = SDL_CreateWindow("Dreamers Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	
	if (mainWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	mainBackBuffer = SDL_GetWindowSurface(mainWindow);
	return true;
}
void GameGraphics::Render()
{
	SDL_UpdateWindowSurface(mainWindow);
}