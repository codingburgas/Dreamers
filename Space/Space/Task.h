#pragma once
#include <string>
class Task
{
public:
	int level;
	int goal;
	int currentScore = 0;
	Task(int goal,
		int level) : goal(goal),level(level) {}

	void evaluateScore()
	{
		currentScore++;
	}
};