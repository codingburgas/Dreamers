#pragma once
#include <SDL.h> // Include the SDL library
#include <iostream>

class GameGraphics {

public:

	// Constants for screen size
	static const int screenWidth = 800;
	static const int screenHeight = 600;

	static GameGraphics* Instance(); // Singleton pattern: get the Instance of GameGraphics

	static void Release(); // Singleton pattern: get the Instance of GameGraphics

	static bool Initialized(); 

	void Render(); // Render function to display graphics

private:

	static GameGraphics* singletonInstance;
	static bool singletonInitialized;

	SDL_Window* mainWindow; // SDL window used for rendering
	SDL_Surface* mainBackBuffer;

	GameGraphics(); // Constructor to enforce singleton pattern
	~GameGraphics(); // Destructor to clean up resources

	bool Init(); // Initialize the GameGraphics instance
};