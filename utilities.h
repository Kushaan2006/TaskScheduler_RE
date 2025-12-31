/*
	Task Scheduler
	Author: Kushaan Vir Singh
	Personal project for learning C++ multithreading and scheduling.
*/


#ifndef SCHEDULER_UTILITIES_H
#define SCHEDULER_UTILITIES_H

#include<iostream>
#include<chrono>

namespace scheduler
{
	class utils
	{
	public:
		std::chrono::time_point<std::chrono::system_clock>
			stotp(const std::string& time);

		char* stoc(const std::string& str) const;
	};

	extern utils ut;
}

#endif // !SCHEDULER_UTILITIES_H
