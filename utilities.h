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
	};

	extern utils ut;
}

#endif // !SCHEDULER_UTILITIES_H
