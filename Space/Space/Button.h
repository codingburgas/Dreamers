#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Button {
public:
	SDL_Rect buttonRect;

	Button(int xStart, int yStart, int xEnd, int yEnd);

	bool isMouseOverButton(int mouseX, int mouseY);

	void handleButtonClick();

	void exitGame();

	void stepsGame();
};
