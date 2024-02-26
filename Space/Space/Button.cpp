#include "Button.h"

// Constructor for creating a button with given coordinates
Button::Button(int xStart, int yStart, int xEnd, int yEnd, AppState state, bool (*callBack)())
{
	// Initialize the buttonRect with the specified coordinates
	buttonRect = { xStart, yStart, xEnd, yEnd };

	this->callBack = callBack;
	this->state = state;
}

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

bool Button::click(int mousePositionX, int mousePositionY, AppState currentState)
{
	// It checks if the mouse is over the button and the current state matches the button's state.
	if (isMouseOverButton(mousePositionX, mousePositionY) && currentState == state)
	{
		// If both conditions are met, it calls the callback function associated with the button and returns true.
		return callBack();
	}
	return false;
}


