#pragma once
#include <map>
#include <vector>
#include "Task.h"
class TaskManager
{
public:
	std::vector<Task> tasks;
	TaskManager()
	{
		tasks = std::vector<Task>
		{
			Task(6, 0),
			Task(5, 0),
			Task(10, 0),
			Task(10, 0),

			Task(6, 1),
			Task(5, 1),
			Task(10, 1),
			Task(10, 1),

			Task(6, 2),
			Task(5, 2),
			Task(10, 2),
			Task(10, 2),

			Task(6, 3),
			Task(5, 3),
			Task(10, 3),
			Task(10, 3),
		};
	}

	void EvaluateScore(int level)
	{
		for (size_t i = 0; i < tasks.size(); i++)
		{
			if (tasks[i].level == level)
			{
				if (tasks[i].currentScore == tasks[i].goal)
				{
					continue;
				}
				else
				{
					tasks[i].currentScore++;
					break;
				}
			}
		}
	}

	std::string GetTaskText(int level, int index)
	{
		bool flag = false;
		for (size_t i = 0; i < tasks.size(); i++)
		{
			if (tasks[i].level == level)
			{
				flag = true;
			}
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
};