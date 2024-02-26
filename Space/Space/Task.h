#pragma once
#include <string>
class Task
{
public:
	// Variables to store task information
	int level;
	int goal;
	int currentScore = 0;

	// Constructor to initialize the task with a goal and level
	Task(int goal,
		int level) : goal(goal),level(level) {}

	// Function to evaluate the player's score and progress towards completing the task
	void evaluateScore()
	{
		// Increment currentScore by 1
		currentScore++;
	}
};