#include<iostream>
#include<chrono>
#include<thread>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>

#include"task.h"
#include"scheduler.h"
#include"utilities.h"

namespace scheduler
{
	int Sched::task_id_track = 0;

	Sched::Sched()
	{
		loadTasks();
	}

	void Sched::newTask(const std::string task, const std::string msg, const std::string time, const int type, const std::string path)
	{

		/*Task obj(task, msg, time, type, path, ++task_id_track);
		tasks.push_back(std::move(obj));*/

		tasks.emplace_back(task, msg, time, type, path, ++task_id_track);
		
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

	void Sched::loadTasks()
	{
		std::ifstream file("automator_save_state.txt");

		if (!file)
			return;
		
		

		std::string task_id, task_complete, task_name, task_msg, task_path, task_type, exe_time;

		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream ss(line);

			std::getline(ss, task_id, ',');
			std::getline(ss, task_complete, ',');
			std::getline(ss, task_name, ',');
			std::getline(ss, task_msg, ',');
			std::getline(ss, task_path, ',');
			std::getline(ss, task_type, ',');
			std::getline(ss, exe_time);

			if (std::stoi(task_complete) != 1)
			{
				int task_time = std::stoi(task_type);


				//task, msg, time, type, path, ++task_id_track
				newTask(
					task_name,
					task_msg,
					exe_time,
					task_time,
					task_path
				);

			}

		}

	}

	void Sched::stop()
	{
		saveTasks();
	}

	Sched::~Sched()
	{
		
		setStopper();
		saveTasks();
	}

}