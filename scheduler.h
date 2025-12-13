#ifndef SCHEDULER_SCHEDULER_H
#define SCHEDULER_SCHEDULER_H

#include<deque>

#include"task.h"
#include"scheduler.h"
#include"utilities.h"


namespace scheduler
{
	class Sched
	{
		std::deque<Task> tasks;
		
	public:
		void newTask(const std::string& task, const std::string& msg, const std::string& time, const int& type, const std::string& path);
		void exeAllTask();
		void setStopper();
		~Sched();
	};
}

#endif // !SCHEDULER_SCHEDULER_H
