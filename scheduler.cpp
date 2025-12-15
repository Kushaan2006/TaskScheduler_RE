#include<iostream>
#include<chrono>
#include<thread>
#include<vector>
#include<fstream>

#include"task.h"
#include"scheduler.h"
#include"utilities.h"

namespace scheduler
{
	int Sched::task_id_track = 0;

	void Sched::newTask(const std::string& task, const std::string& msg, const std::string& time, const int& type, const std::string& path)
	{

		Task obj(task, msg, time, type, path, ++task_id_track);
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

	void Sched::saveTasks()
	{
		std::ofstream fout("automator_save_state.txt");

		if (!fout)
			return;

		for (const auto& it : tasks)
		{
			it.write(fout);
		}

		fout.close();
	}

	Sched::~Sched()
	{
		saveTasks();
		setStopper();
	}

}