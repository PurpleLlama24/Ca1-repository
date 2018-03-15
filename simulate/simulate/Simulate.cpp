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
void averageResponseTime(vector<Job> jobvector);
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
		averageResponseTime(jobVector);
		jobFile.close();
		system("pause");
	}
	else
	{
		cout << "error opening file" << endl;

	}
	return 0;

}
//making a string from the text file.
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
//turning the string from the split function into vectors of jobs.
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
//print the jobs and their details plainly
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
//sorting the jobs by the time they arrive specified by the textfile
vector<Job> sortByArrival(vector<Job>jobVector)
{
	vector<Job> outVector;
	//set the earliest as the first in the textfile
	int earliestArrivalTime = jobVector.at(0).arrivalTime;
	//run until the vector is empty
	while (jobVector.size() != 0)
	{
		for (int i = 0; i < jobVector.size(); i++)
		{
			if (jobVector.at(i).arrivalTime < earliestArrivalTime)
			{
				//if another time is smaller, change the smallest value.
				earliestArrivalTime = jobVector.at(i).arrivalTime;
			}
		}
		for (int i = 0; i < jobVector.size(); i++)
		{
			if (earliestArrivalTime == jobVector.at(i).arrivalTime)
			{
				//when a value in the vector has an arrival time equal the smallest add it to the out vector
				outVector.push_back(jobVector.at(i));
				//remove the job from the original vector
				jobVector.erase(jobVector.begin() + i);
			}
		}
		if (jobVector.size() != 0)
		{
			//reset the earliest arrival time when the vector is not empty.
			earliestArrivalTime = jobVector.at(0).arrivalTime;
		}
	}
	return outVector;
}
vector<Job> sortByDuration(vector<Job>jobVector)
{
	vector<Job> outVector;
	//set the earliest as the first in the textfile
	int shortestDuration = jobVector.at(0).duration;
	//run until the vector is empty
	while (jobVector.size() != 0)
	{
		for (int i = 0; i < jobVector.size(); i++)
		{
			if (jobVector.at(i).duration < shortestDuration)
			{
				//if another duration is smaller, change the smallest value.
				shortestDuration = jobVector.at(i).duration;
			}
		}
		for (int i = 0; i < jobVector.size(); i++)
		{
			if (shortestDuration == jobVector.at(i).duration)
			{
				//when a value in the vector has a duration time equal the smallest add it to the out vector
				outVector.push_back(jobVector.at(i));
				//remove the job from the original vector
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
//actually only get the one with the longest time to completion...
vector<Job> shortestTimeToCompletion(vector <Job> jobVector)
{
	//uses a vector sorted by arrival time
	vector<Job> arrivalOrder = sortByArrival(jobVector);
	vector<Job> ttcOrderB;
	int totalTimetoCompletion = 0;
	Job longestToCompletion;
	int shortestTimeToCompletion = 0;
	int currentMax = 0;
	int incrementer = 0;
	//sets a basic time to completion to the arrival time of a job and its duration
	for each (Job  j in arrivalOrder)
	{
		totalTimetoCompletion += j.arrivalTime + j.duration;
	}
	//increments simualte 'ticks' of the machine and the current number since the program started
	while (incrementer <= totalTimetoCompletion)
	{
		for each (Job j in arrivalOrder)
		{
			if (incrementer == j.arrivalTime)
			{
				//time  for each job is it's potential start time is its arrival time + the current time, -1
				j.startTime = j.arrivalTime + incrementer - 1;
				//time a job needs to complete is it's start, its duration and the current increment
				j.timeToComplete = j.startTime + j.duration + incrementer;
			}
		}
		for each (Job s in arrivalOrder)
		{
			s.timeToComplete = s.startTime + s.duration + incrementer;
			//finds the maximum to completion time for the jobs
			if (s.timeToComplete > currentMax)
			{
				currentMax = s.timeToComplete;
				//saves the longest to complete
				longestToCompletion = s;
			}
		}
		//increases the 'tick'
		incrementer++;
	}
	//adds the longet time job to a new vector to be returned.
	ttcOrderB.push_back(longestToCompletion);
	return ttcOrderB;
}



vector<Job> roundRobin(vector<Job> jobVector)
{
	vector<Job> arrivedJobs;
	vector<Job> finishOrder;
	//gets the maximums it could take for the whole process to finish.
	int maxIncrement = sortByArrival(jobVector).at(4).arrivalTime;
	int maxDuration = sortByDuration(jobVector).at(4).duration;
	int incrementer = 0;
	int durationIncrementer = 0;
	int removedJobs = 0;
	int maxTTC = maxDuration + maxIncrement;
	// as long as the time isn't gone to the possible maximum, the program will continue.
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
				//decrements the jobs that have arrived by how much time/ticks have passed.
				j.timeToComplete = j.arrivalTime + j.duration - durationIncrementer;
				if (j.timeToComplete > 0) {
					cout << "NAME: " << j.name << " REMIANING TIME: " << j.timeToComplete << endl;
				}
				else if (j.timeToComplete == 0)
				{
					//prints a job once it's time is up.
					cout << j.name << " Finished!" << endl;
				}
			}

		}
		durationIncrementer++;
	}
	return arrivedJobs;
}
//avrages of saved vectors.
void averageResponseTime(vector<Job> jobvector)
{
	vector<Job> arriveOrder = sortByArrival(jobvector);
	vector<Job> shortestOrder = sortByDuration(jobvector);

	int responseByArrival = (arriveOrder.at(4).arrivalTime + arriveOrder.at(4).duration) / 4;
	int responseByshortestorder = (shortestOrder.at(4).arrivalTime + shortestOrder.at(4).duration) / 4;

	cout << "Average by arrival time :  " << responseByArrival << endl;
	cout << "Average by shortest first :  " << responseByshortestorder << endl;

	int maxIncrement = sortByArrival(jobvector).at(4).arrivalTime;
	int maxDuration = sortByDuration(jobvector).at(4).duration;

	int maxTTC = maxDuration + maxIncrement;

	int averageTTC = maxTTC / 5;
	cout << "Average by tim to completion :  " << averageTTC << endl;
}