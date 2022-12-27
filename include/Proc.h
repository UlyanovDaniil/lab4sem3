#pragma once
#include "Queue.h"

class TProc
{
private:
	double ProcRate;
	TQueue<int> Jobs;
	int JobsDone;
	int OverflowTimes;
	int NoJobsTimes;
public:
	TProc(double Rate, int MaxJobs);
	double GetRate();
	int IsProcBusy();
	bool IsProcFull();
	int RunNewJob(int JobId);
	int DoJob();
	int GetJobsDone();
	int GetOverflowTimes();
	int GetNoJobsTimes();
};

TProc::TProc(double Rate, int MaxJobs) : Jobs(MaxJobs)
{
	if (Rate >= 0.0 && Rate <= 1.0)
	{
		ProcRate = Rate;
		JobsDone = 0;
		OverflowTimes = 0;
		NoJobsTimes = 0;
	}
	else
		throw "Proc != [0,1]";
}

inline double TProc::GetRate()
{
	return ProcRate;
}

inline int TProc::IsProcBusy()
{
	if (Jobs.isEmpty())
		return 0;
	else
		return Jobs.Top();
}

inline bool TProc::IsProcFull()
{
	return Jobs.isFull();
}

inline int TProc::RunNewJob(int JobId)
{
	if (JobId > 0)
	{
		if (IsProcFull())
		{
			OverflowTimes++;
			return 0;
		}
		else
		{
			Jobs.Push(JobId);
			return JobId;
		}
	}
	else
		return 0;
}

inline int TProc::DoJob()
{
	if (!IsProcBusy())
	{
		NoJobsTimes++;
		return 0;
	}
	else if ((double)(std::rand()) / (RAND_MAX) <= ProcRate && IsProcBusy())
	{
		int LastJob = Jobs.Pop();
		JobsDone++;
		return LastJob;
	}
	else
		return Jobs.Top();
}

inline int TProc::GetJobsDone()
{
	return JobsDone;
}

inline int TProc::GetOverflowTimes()
{
	return OverflowTimes;
}

inline int TProc::GetNoJobsTimes()
{
	return NoJobsTimes;
}
