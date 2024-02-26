#pragma once
// Include the SDL library
#include <SDL.h> 
#include <SDL_image.h>
#include <string>
#include <iostream>

class Mouse;
class GameGraphics {

public:
	SDL_Renderer* renderer;

	// Constants for screen size
	static const int screenWidth = 1000;
	static const int screenHeight = 600;

	// Singleton pattern: get the Instance of GameGraphics
	static GameGraphics* Instance(); 

	// Singleton pattern: get the Instance of GameGraphics
	static void release(); 

	static bool initialized();

	// Load a texture from the specified file path and return the created SDL_Texture*
	SDL_Texture* loadTexture(std::string path); 
	void clearBackBuffer();

	// Draw the provided SDL_Texture* to the entire screen
	void drawTexture(SDL_Texture* texture); 
	// Draw the provided SDL_Texture* to the entire screen
	void drawTexture(SDL_Texture* texture, SDL_Rect* destinationRect); 

	// Render function to display graphics
	void render(); 

private:

	static GameGraphics* singletonInstance;
	static bool singletonInitialized;

	// SDL window used for rendering
	SDL_Window* mainWindow; 
	SDL_Surface* mainBackBuffer;

	// Constructor to enforce singleton pattern
	GameGraphics();
	// Destructor to clean up resources
	~GameGraphics(); 

	// Initialize the GameGraphics instance
	bool Init(); 
};