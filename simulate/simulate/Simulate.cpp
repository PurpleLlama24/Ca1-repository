#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include "Job.h"
#include <cstdlib>
using namespace std;

vector<string> split(string data, string delimiter);
vector<Job> makeJobs(string jobData);
vector<Job> sortByArrival(vector<Job> jobVector);
vector<Job> sortByDuration(vector<Job> jobVector);
vector<Job> roundRobin(vector<Job> jobVector);
vector<Job> sortByDuration(vector<Job>jobVector);
vector<Job> shortestTimeToCompletion(vector <Job> jobVector);
void printJobs(vector<Job> jobVector);
string jobData;
ifstream jobFile("C://textbasedFile/fileData.txt");


int main()
{
	if (jobFile)
	{
		getline(jobFile, jobData);
		cout << "File found!";
		vector<Job> jobVector = makeJobs(jobData);
		cout << "All jobs in text file order:" << endl;
		printJobs(jobVector);
		cout << "All jobs in arrival order:" << endl;
		vector<Job> arrivalSorted = sortByArrival(jobVector);
		printJobs(arrivalSorted);
		cout << "All jobs in shortest duration:" << endl;
		vector<Job> durationSorted = sortByDuration(jobVector);
		printJobs(durationSorted);
		cout << "All jobs in shortest time to completion:" << endl;
		vector<Job> roundRobinSorting = roundRobin(jobVector);
		cout << "Jobs in time to completion order" << endl;
		vector<Job> timeToCompletonOrder = shortestTimeToCompletion(jobVector);
		printJobs(timeToCompletonOrder);

		jobFile.close();
	}
	else
	{
		cout << "error opening file" << endl;

	}
	return 0;

}

vector<string> split(string jobData, string delimiter)
{
	vector< string> outVector;
	string strElement;
	size_t oldPos = -1;
	size_t pos = jobData.find(delimiter, oldPos + 1);
	while (pos != string::npos)
	{
		strElement = jobData.substr(oldPos + 1, pos - oldPos - 1);
		outVector.push_back(strElement);
		oldPos = pos;
		pos = jobData.find(delimiter, oldPos + 1);
	}
	return outVector;
}

vector<Job>makeJobs(string jobData)
{

	vector<string> jobDetails = split(jobData, " ");
	vector<Job> jobVector;
	int i = 0;
	for each (string s in jobDetails)
	{
		i++;
	}
	for (int k = 0; k < (i / 3); k++)
	{

		Job j;
		j.name = jobDetails[(0 + (k * 3))];  // source : http://www.cplusplus.com/forum/general/13135/
		j.arrivalTime = atoi(jobDetails[(1 + (k * 3))].c_str());
		j.duration = atoi(jobDetails[(2 + (k * 3))].c_str());
		jobVector.push_back(j);
	}
	return jobVector;
}
void printJobs(vector<Job> jobVector)
{

	for (int i = 0; i < jobVector.size(); i++)
	{
		Job j = jobVector.at(i);
		cout << "Name: " << j.name << endl;
		cout << "Arrival time: " << j.arrivalTime << endl;
		cout << "Duration: " << j.duration << endl;
	}
}

vector<Job> sortByArrival(vector<Job>jobVector)
{
	vector<Job> outVector;
	int earliestArrivalTime = jobVector.at(0).arrivalTime;
	while (jobVector.size() != 0)
	{
		for (int i = 0; i < jobVector.size(); i++)
		{
			if (jobVector.at(i).arrivalTime < earliestArrivalTime)
			{
				earliestArrivalTime = jobVector.at(i).arrivalTime;
			}
		}
		for (int i = 0; i < jobVector.size(); i++)
		{
			if (earliestArrivalTime == jobVector.at(i).arrivalTime)
			{
				outVector.push_back(jobVector.at(i));
				jobVector.erase(jobVector.begin() + i);
			}
		}
		if (jobVector.size() != 0)
		{
			earliestArrivalTime = jobVector.at(0).arrivalTime;
		}
	}
	return outVector;
}
vector<Job> sortByDuration(vector<Job>jobVector)
{
	vector<Job> outVector;
	int shortestDuration = jobVector.at(0).duration;
	while (jobVector.size() != 0)
	{
		for (int i = 0; i < jobVector.size(); i++)
		{
			if (jobVector.at(i).duration < shortestDuration)
			{
				shortestDuration = jobVector.at(i).duration;
			}
		}
		for (int i = 0; i < jobVector.size(); i++)
		{
			if (shortestDuration == jobVector.at(i).duration)
			{
				outVector.push_back(jobVector.at(i));
				jobVector.erase(jobVector.begin() + i);
			}
		}
		if (jobVector.size() != 0)
		{
			shortestDuration = jobVector.at(0).duration;
		}
	}
	return outVector;
}
vector<Job> shortestTimeToCompletion(vector <Job> jobVector)
{
	vector<Job> arrivalOrder = sortByArrival(jobVector);
	vector<Job> ttcOrderB;
	int totalTimetoCompletion = 0;
	Job longestToCompletion;
	int shortestTimeToCompletion = 0;
	int currentMax = 0;
	int incrementer = 0;
	for each (Job  j in arrivalOrder)
	{
		totalTimetoCompletion += j.arrivalTime + j.duration;
	}

	while (incrementer <= totalTimetoCompletion)
	{
		for each (Job j in arrivalOrder)
		{
			if (incrementer == j.arrivalTime)
			{
				j.startTime = j.arrivalTime + incrementer - 1;
				j.timeToComplete = j.startTime + j.duration + incrementer;
			}
		}
		for each (Job s in arrivalOrder)
		{

			s.timeToComplete = s.startTime + s.duration + incrementer;
			if (s.timeToComplete > currentMax)
			{
				currentMax = s.timeToComplete;
				longestToCompletion = s;
			}
		}

		incrementer++;
	}
	ttcOrderB.push_back(longestToCompletion);
	return ttcOrderB;
}

vector<Job> roundRobin(vector<Job> jobVector)
{
	vector<Job> arrivedJobs;
	vector<Job> finishOrder;
	int maxIncrement = sortByArrival(jobVector).at(4).arrivalTime;
	int maxDuration = sortByDuration(jobVector).at(4).duration;
	int incrementer = 0;
	int durationIncrementer = 0;
	int removedJobs = 0;
	int maxTTC = maxDuration + maxIncrement;
	while (incrementer <= maxIncrement)
	{
		for each (Job j in jobVector)
		{
			if (j.arrivalTime == incrementer)
			{
				arrivedJobs.push_back(j);
			}
		}
		incrementer++;
	}
	while (durationIncrementer < maxTTC) {
		for each (Job j in arrivedJobs)
		{
			if (j.arrivalTime <= durationIncrementer)
			{
				j.timeToComplete = j.arrivalTime + j.duration - durationIncrementer;
				if (j.timeToComplete > 0) {
					cout << "NAME: " << j.name << " REMIANING TIME: " << j.timeToComplete << endl;
				}
				else if (j.timeToComplete == 0)
				{
					cout << j.name << "Finished!" << endl;
				}
			}

		}
		durationIncrementer++;
	}
	return arrivedJobs;
}
