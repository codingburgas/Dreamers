#pragma once
#include <string>
class Task
{
private:
	int goal;
	int currentScore;
public:
	Task(int goal,
		 int currentScore) : goal(goal), currentScore(currentScore) {}

	void evaluateScore()
	{
		currentScore++;
	}
};