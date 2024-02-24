#pragma once
#include <string>
#include <vector>
#include "Task.h"
class TaskManager
{
private:
	std::vector<Task> tasks;
public:
	void Render()
	{
		for (size_t i = 0; i < tasks.size(); i++)
		{

		}
	}
};