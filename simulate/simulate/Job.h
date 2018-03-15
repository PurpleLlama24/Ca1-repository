#pragma once
#include <string>
class Job
{
public:
	Job();
	~Job();

	std::string name;
	int arrivalTime;
	int duration;
	int timeToComplete = arrivalTime + duration;
	int startTime;
};

