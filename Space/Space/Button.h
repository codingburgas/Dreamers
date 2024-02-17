#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Button {
public:
	SDL_Rect buttonRect; // Rectangle representing the button's position and size

	Button(int xStart, int yStart, int xEnd, int yEnd); // Constructor for creating a button with given coordinates

	bool isMouseOverButton(int mousePositionX, int mousePositionY); // Check if the mouse is over the button

	void startGame(); // Handle button click action for start button

	void exitGame(); // Handle button click action for exit button

	void stepsGame(); // Handle button click action for steps button
};