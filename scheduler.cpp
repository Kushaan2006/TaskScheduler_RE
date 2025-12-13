#include<iostream>
#include<chrono>
#include<thread>
#include<vector>

#include"task.h"
#include"scheduler.h"
#include"utilities.h"

namespace scheduler
{
	void Sched::newTask(const std::string& task, const std::string& msg, const std::string& time, const int& type, const std::string& path)
	{
		Task obj(task, msg, time, type, path);
		tasks.push_back(std::move(obj));
		auto& it = tasks.back();
		it.threadIt();
	}

	void Sched::exeAllTask()
	{
		for (auto it = tasks.begin(); it < tasks.end(); ++it )
		{
			(*it).joinIt();
			//if ((*it).getThreadStatus() != 1)
			//{
			//	
			//}
		}
	}

	void Sched::setStopper()
	{
		for (auto it = tasks.begin(); it < tasks.end(); ++it)
		{
			(*it).joinIt();
			//if ((*it).getThreadStatus() != 0)
			//{
			//	
			//}
		}
	}

	Sched::~Sched()
	{
		setStopper();
	}

}