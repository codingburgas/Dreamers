#pragma once
#include <string>
class Task
{
private:
	std::string title;
	std::string task;
	std::string imagePath;
	int goal;
	int currentScore;
public:
	Task(std::string title,
		std::string task,
		std::string imagePath,
		int goal,
		int currentScore) : title(title), task(task), imagePath(imagePath), goal(goal), currentScore(currentScore) {}

	void evaluateScore()
	{
		currentScore++;
	}
};