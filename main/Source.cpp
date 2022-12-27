#include <iostream>
#include "Queue.h"
#include "JobStream.h"
#include "Proc.h"

int main()
{
  TQueue<int> q1(4), q2(q1);

  q1.Push(2);
  q1.Push(3);
  q1.Push(4);

  std::cout << q1.Top() << "\n";

  std::cout << q1.Pop() << "\n";

  std::cout << q1.Top() << "\n";
	
	std::srand(std::time(nullptr));
	const int tests = 3;
	TProc proc[tests] = { TProc(0.5, 3), TProc(0.2, 3), TProc(0.5, 3) };
	TJobStream stream[tests] = { TJobStream(0.5), TJobStream(0.5), TJobStream(0.2) };
	int tacts[tests] = { 10, 10, 10 };
	TQueue<int> jobsqueue(10);

	for (int i = 0; i < tests; i++)
	{
		std::cout << tacts[i] << " tacts, queue size is 3, JobsIntense is " << stream[i].GetJobIntens() << ", proc rate is " << proc[i].GetRate() << '.' << std::endl;
		for (int j = 0; j < tacts[i]; j++)
		{
			int temp_job = stream[i].GetNewJob();
			if (temp_job > 0)
				jobsqueue.Push(temp_job);
			if (!jobsqueue.isEmpty())
				if (proc[i].RunNewJob(jobsqueue.Top()))
					jobsqueue.Pop();
			proc[i].DoJob();
		}
		jobsqueue.Free();
		std::cout << "Jobs Generated " << stream[i].GetLastJobId() << ", Proc Jobs Done " << proc[i].GetJobsDone() << ", Proc Jobs Overflow " << proc[i].GetOverflowTimes() << ", Proc No Jobs Tacts " << proc[i].GetNoJobsTimes() << ", average " << ((double)(tacts[i]) / (double)(proc[i].GetJobsDone())) << " tacts done per job." << std::endl << std::endl;
	}
	return 0;
}