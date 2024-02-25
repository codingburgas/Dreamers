#include "Graphics.h"

GameGraphics* GameGraphics::singletonInstance = nullptr;
bool GameGraphics::singletonInitialized = false;

GameGraphics* GameGraphics::Instance()
{
	if (singletonInstance == nullptr)
	{
		singletonInstance = new GameGraphics(); // Create a new GameGraphics instance and assing it to singletonInstance
	}
	return singletonInstance;

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
	SDL_DestroyRenderer(renderer); // Destroy the SDL renderer and set the pointer to NULL for safety

	IMG_Quit();
	SDL_Quit(); // Quit the SDL subsystem, releasing resources
}

// Initialize SDL and create the main window
bool GameGraphics::Init()
{
	// Initializes the SDL video subsystem for handling graphical output
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	// Create a window at the specified position with given dimensions
	mainWindow = SDL_CreateWindow("Dreamers Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	
	// Check if window creation was succesful
	if (mainWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	// Create a rednerer for the main window with accelerated rendering
	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer Creation Error: %s\n", SDL_GetError());
		return false;
	}
	// Set the render draw color to white
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Initialize the IMG library for PNG image loading
	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) {
		printf("IMG Initialization Error: %s\n", IMG_GetError());
		return false;
	}

	bool quit = false;
	SDL_Event mainEvents;

	// Get the main surface of the window
	mainBackBuffer = SDL_GetWindowSurface(mainWindow);
	return true;
}

// This function loads a texture from a specified file path
SDL_Texture* GameGraphics::LoadTexture(std::string path)
{
	SDL_Texture* texture=NULL;
	// Load the image surface from the file path
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL)
	{
		printf("Image Load Error: Path(%s) -Error %s\n", path.c_str(), IMG_GetError());
		return texture;
	}

	// Create a texture from the loaded surface
	texture = SDL_CreateTextureFromSurface(singletonInstance->renderer, surface);
	if (texture == nullptr)
	{
		printf("Create Texture Error: %s\n", SDL_GetError());
		return texture;
	}

	// Free the surface as it's no longer needed
	SDL_FreeSurface(surface);
	return texture; // Return the created texture
}

void GameGraphics::ClearBackBuffer() {
	SDL_RenderClear(singletonInstance->renderer);
}

// Draw the texture to the entire screen
void GameGraphics::DrawTexture(SDL_Texture* texture) {
	// The entire texture will be drawn at its ariginal size and positions
	SDL_RenderCopy(singletonInstance->renderer, texture, nullptr, nullptr);
}

void GameGraphics::DrawTexture(SDL_Texture* texture, SDL_Rect* destinationRect)
{
	SDL_RenderCopy(singletonInstance->renderer, texture, nullptr, destinationRect);
}

// Update the window surface
void GameGraphics::Render()
{
	SDL_RenderPresent(singletonInstance->renderer);  // Present the rendered graphics on the screen using the SDL renderer
}