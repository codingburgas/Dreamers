#pragma once
#include <map>
#include <vector>
#include "Task.h"

// This TaskManager class manages a set of tasks for different levels.
class TaskManager
{
public:
	std::vector<Task> tasks;
	// Constructor to initialize the TaskManager with a set of tasks for different levels.
	TaskManager();

	// Function to evaluate the player's score for tasks in a specific level.
	void evaluateScore(int level);

	// Function to get the text of a task based on the level and index.
	// Parameters:
	// - level: The level of the task
	// - index: The index of the task
	std::string GetTaskText(int level, int index);
};