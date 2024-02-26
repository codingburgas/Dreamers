#include "Timer.h"
#include <SDL.h>

Timer* Timer::singletonInstance = NULL;
// Creates and returns a single instance of Timer, ensuring only one exists
Timer* Timer::Instance() {
	if (singletonInstance == NULL)
	{
		singletonInstance = new Timer();
		return singletonInstance;
	}
}

void Timer::release()
{
	delete singletonInstance;
	singletonInstance = NULL;
}

Timer::Timer()
{
	// Set the Timer to its original state
	reset(); 
	// Set the default time scaling factor to 1.0 (normal speed)
	mainTimeScale = 1.0f; 
}
Timer::~Timer() {

}

// Reset the Timer's state
void Timer::reset()
{
	// Record the current ticks as the start time
	mainStartTicks = SDL_GetTicks(); 
	mainElapsedTicks = 0;
	mainDelataTime = 0.0f;
}

// Get the time elapsed since the last frame in seconds
float Timer::deltaTime()
{
	return mainDelataTime;
}
void Timer::timeScale(float t)
{
	mainTimeScale = t;
}
float Timer::timeScale()
{
	return mainTimeScale;
}

// Update the Timer's state based on the current time
void Timer::update()
{
	// Calculate elapsed ticks
	mainElapsedTicks = SDL_GetTicks() - mainStartTicks;
	// Convert elapsed ticks to seconds
	mainDelataTime = mainElapsedTicks * 0.001f;  
}