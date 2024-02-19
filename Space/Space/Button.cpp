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


