#pragma once

class Timer {

public:

	static Timer* Instance();
	static void Release();
	void Reset();

	float DeltaTime(); // Gets the time elapsed since the last frame in seconds 
	void TimeScale(float t); // Sets the time scaling factor
	float TimeScale(); // Gets the current time scaling factor

	void Update();

private:

	static Timer* singletonInstance;
	// Time variables
	unsigned int mainStartTicks;
	unsigned int mainElapsedTicks;

	float mainDelataTime; // Time intervals
	float mainTimeScale; // Time scaling factor applied to control the speed of the time
	
	// Constructor and Destructor
	Timer();
	~Timer();
};
