#pragma once

class Timer {

public:

	static Timer* Instance();
	static void release();
	void reset();

	// Gets the time elapsed since the last frame in seconds 
	float deltaTime(); 
	// Sets the time scaling factor
	void timeScale(float t);
	// Gets the current time scaling factor
	float timeScale(); 

	void update();

private:

	static Timer* singletonInstance;
	// Time variables
	unsigned int mainStartTicks;
	unsigned int mainElapsedTicks;

	// Time intervals
	float mainDelataTime;
	// Time scaling factor applied to control the speed of the time
	float mainTimeScale; 
	
	// Constructor and Destructor
	Timer();
	~Timer();
};
