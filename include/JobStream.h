#pragma once
#include <cstdlib>

class TJobStream
{
private:
	double JobIntense;
	int LastJobId;
public:
	TJobStream(double JobIntens);
	double GetJobIntens();
	int GetNewJob();
	int GetLastJobId();
};

TJobStream::TJobStream(double JobIntens)
{
	if (JobIntens >= 0.0 && JobIntens <= 1.0)
	{
		this->JobIntense = JobIntens;
		LastJobId = 1;
	}
	else
		throw "JobIntens != [0,1]";
}

double TJobStream::GetJobIntens()
{
	return JobIntense;
}

int TJobStream::GetNewJob()
{
	if (((double)rand()) / (RAND_MAX) <= JobIntense)
	{
		LastJobId++;
		return LastJobId - 1;
	}
	else
		return 0;
}

int TJobStream::GetLastJobId()
{
	return LastJobId;
}