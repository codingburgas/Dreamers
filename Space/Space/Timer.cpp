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

void Timer::Release()
{
	delete singletonInstance;
	singletonInstance = NULL;
}

Timer::Timer()
{
	Reset(); // Set the Timer to its original state
	mainTimeScale = 1.0f; // Set the default time scaling factor to 1.0 (normal speed)
}
Timer::~Timer() {

}

// Reset the Timer's state
void Timer::Reset()
{
	mainStartTicks = SDL_GetTicks(); // Record the current ticks as the start time
	mainElapsedTicks = 0;
	mainDelataTime = 0.0f;
}

// Get the time elapsed since the last frame in seconds
float Timer::DeltaTime()
{
	return mainDelataTime;
}
void Timer::TimeScale(float t)
{
	mainTimeScale = t;
}
float Timer::TimeScale()
{
	return mainTimeScale;
}

// Update the Timer's state based on the current time
void Timer::Update()
{
	mainElapsedTicks = SDL_GetTicks() - mainStartTicks; // Calculate elapsed ticks
	mainDelataTime = mainElapsedTicks * 0.001f; // Convert elapsed ticks to seconds 
}