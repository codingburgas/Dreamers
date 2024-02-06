#include "Graphics.h"
#include <iostream>

GameGraphics* GameGraphics::sInstance = NULL;
bool GameGraphics::sInitialized = false;

GameGraphics* GameGraphics::Instance()
{
	if (sInstance == NULL)
		sInstance = new GameGraphics();
	return sInstance;
}

void GameGraphics::Release()
{
	delete sInstance;
	sInstance = NULL;

	sInitialized = false;
}
bool GameGraphics::Initialized()
{
	return Initialized;
}

GameGraphics::GameGraphics() {
	mBackBuffer = NULL;
	sInitialized = Init();
}
GameGraphics::~GameGraphics()
{
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	SDL_DestroyRenderer(mRenderer);
	IMG_Quit();
	SDL_Quit();
}

bool GameGraphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	//Get window surface
	mBackBuffer = SDL_GetWindowSurface(mWindow);
	if (mBackBuffer == NULL)
	{
		printf("SDL surface could not be loaded! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	//Fill the surface white
	SDL_FillRect(mBackBuffer, NULL, SDL_MapRGB(mBackBuffer->format, 0xFF, 0xFF, 0xFF));

	//Update the surface
	SDL_UpdateWindowSurface(mWindow);

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == NULL)
	{
		printf("Renderer Creation Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	int flags = IMG_INIT_PNG;
	if (!IMG_Init(flags) & flags)
	{
		printf("IMG Initialization Error: %s\n", IMG_GetError());
		return false;
	}
	mBackBuffer = SDL_GetWindowSurface(mWindow);
	return true;

}

SDL_Texture* GameGraphics::LoadTexture(std::string path)
{
	SDL_Texture* tex = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL)
	{
		printf("Image Load Error: Path(%s)-Error(%s)\n", path.c_str(), IMG_GetError());
		return tex;
	}
	tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (tex == NULL)
	{
		printf("Create Texture Error: %s\n", SDL_GetError());
		return tex;
	}

	SDL_FreeSurface(surface);
	return tex;
}

void GameGraphics::ClearBackBuffer()
{
	SDL_RenderClear(mRenderer);
}
void GameGraphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend)
{
	SDL_RenderCopy(mRenderer, tex, clip, rend);
}

void GameGraphics::Render()
{
	SDL_RenderPresent(mRenderer);

}