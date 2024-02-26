#include "TaskManager.h"

TaskManager::TaskManager()
{
	tasks = std::vector<Task>
	{
		Task(8, 0),
		Task(5, 0),
		Task(7, 0),

		Task(5, 1),
		Task(10, 1),
		Task(3, 1),
		Task(7, 1),

		Task(6, 2),
		Task(5, 2),
		Task(15, 2),
		Task(4, 2),

		Task(14, 3),
		Task(5, 3),
		Task(10, 3),
		Task(6, 3),
	};
}

void TaskManager::evaluateScore(int level)
{
	for (size_t i = 0; i < tasks.size(); i++)
	{
		// Check if the task belongs to the input level
		if (tasks[i].level == level)
		{
			// Check if the task has reached its goal score
			if (tasks[i].currentScore == tasks[i].goal)
			{
				// Skip to the next task if the goal is reached
				continue;
			}
			else
			{
				// Increment the current score of the task
				tasks[i].currentScore++;
				break;
			}
		}
	}
}

std::string TaskManager::GetTaskText(int level, int index)
{
	bool flag = false;
	for (size_t i = 0; i < tasks.size(); i++)
	{
		// If it finds a task with the specified level, it sets a flag to true.
		if (tasks[i].level == level)
		{
			flag = true;
		}
		// When the index reaches - 1, it returns a string representing the current score and goal of the task at that level and index.
		if (flag)
		{
			index--;
		}
		if (index == -1)
		{
			return std::to_string(tasks[i].currentScore) + "/" + std::to_string(tasks[i].goal);
		}
	}
	return "";
}