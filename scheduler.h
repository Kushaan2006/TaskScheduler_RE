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
		static int task_id_track;
		
	public:
		void newTask(const std::string& task, const std::string& msg, const std::string& time, const int& type, const std::string& path);
		void exeAllTask();
		void setStopper();
		void saveTasks();
		void firstExe();
		~Sched();
	};
}

#endif // !SCHEDULER_SCHEDULER_H
