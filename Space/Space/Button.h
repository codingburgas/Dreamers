#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "AppStates.h"

class Button {
private:
	AppState state;
	void (*callBack)();
public:
	SDL_Rect buttonRect; // Rectangle representing the button's position and size

	Button(int xStart, int yStart, int xEnd, int yEnd, AppState state, void (*callBack)()); // Constructor for creating a button with given coordinates
	Button(int xStart, int yStart, int xEnd, int yEnd); // Constructor for creating a button with given coordinates


	bool isMouseOverButton(int mousePositionX, int mousePositionY); // Check if the mouse is over the button

	void click(int mousePositionX, int mousePositionY, AppState currState);
};

