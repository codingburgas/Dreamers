#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "AppStates.h"

class Button {

private:
	AppState state;
	bool (*callBack)();

public:
	// Rectangle representing the button's position and size
	SDL_Rect buttonRect;

	// Constructor for creating a button with given coordinates
	Button(int xStart, int yStart, int xEnd, int yEnd, AppState state, bool (*callBack)());
	// Constructor for creating a button with given coordinates
	Button(int xStart, int yStart, int xEnd, int yEnd); 

	// Check if the mouse is over the button
	bool isMouseOverButton(int mousePositionX, int mousePositionY); 

	bool click(int mousePositionX, int mousePositionY, AppState currState);
};

