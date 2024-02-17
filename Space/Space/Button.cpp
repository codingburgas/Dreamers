#include "Button.h"

// Constructor for creating a button with given coordinates
Button::Button(int xStart, int yStart, int xEnd, int yEnd)
{
	// Initialize the buttonRect with the specified coordinates
	buttonRect = { xStart, yStart, xEnd, yEnd };
}

// Check if the mouse is over the button 
bool Button::isMouseOverButton(int mousePositionX, int mousePositionY) {

	// Check if the mouse coordinates are within the button's boundaries
	return mousePositionX >= buttonRect.x && mousePositionX <= buttonRect.x + buttonRect.w &&
		mousePositionY >= buttonRect.y && mousePositionY <= buttonRect.y + buttonRect.h;
}

// Initialize when the start button is clicked
void Button::startGame() {
	std::cout << "StartButton Clicked!" << std::endl;
}

// Initialize when the exit button is clicked
void Button::exitGame() {
	std::cout << "ExitButton Clicked!" << std::endl;
}


// Initialize when the steps button is clicked
void Button::stepsGame() {
	std::cout << "StepsButton Clicked!" << std::endl;
}

