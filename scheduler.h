/*
	Task Scheduler
	Author: Kushaan Vir Singh
	Personal project for learning C++ multithreading and scheduling.
*/

#ifndef SCHEDULER_SCHEDULER_H
#define SCHEDULER_SCHEDULER_H

#include<deque>
#include <string>

#include"task.h"
#include"utilities.h"


namespace scheduler
{
	class Sched
	{
		std::deque<Task> tasks;
		static int task_id_track;
		utils ut;
		
	public:
		Sched();
		void newTask(const std::string task, const std::string msg, const std::string time, const int type, const std::string path);
		void exeAllTask();
		void setStopper();
		void saveTasks();
		void loadTasks();
		void stop();
		void listAll();
		int getTasksSize();
		~Sched();
	};
}

#endif // !SCHEDULER_SCHEDULER_H
