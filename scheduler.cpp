/*
	Task Scheduler
	Author: Kushaan Vir Singh
	Personal project for learning C++ multithreading and scheduling.
*/


#include<iostream>
#include<chrono>
#include<thread>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>

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

		saveTasks();
	}


	//yet to implement, cant delete tasks yet
	void Sched::listAll()
	{
		system("cls");


		while (1)
		{
			/*std::cout << "All Current Tasks" << std::endl << std::endl;
			std::cout << "No.   Task Name     Task Msg      Task Status" << std::endl;*/

			std::cout << "                   ALL LOADED TASKS                  " << std::endl;
			std::cout << "+----+----------------+----------------+------------+" << std::endl;

			if (this->getTasksSize() == 0)
			{
				std::cout << "|                 NO TASKS AVAILABLE                |" << std::endl;
				std::cout << "+----+----------------+----------------+------------+" << std::endl;
				getchar();
				break;
			}

			int counter = 1;
			for (auto& it : tasks)
			{

				std::string name, msg, status;
				name = it.getName(); 
				msg = it.getMsg();
				if (it.getStatus() == 1)
				{
					/*std::cout << counter++ << "    " << it.getName() << "    " << it.getMsg() << "     " << "COMPLETED" << std::endl;*/
					status = "COMPLETED";
				}
				else if (it.getStatus() == 0)
				{
					/*std::cout << counter++ << "    " << it.getName() << "    " << it.getMsg() << "     " << "PENDING" << std::endl;*/
					status = "PENDING";
				}
				
				else if (it.getTime() < std::chrono::system_clock::now())
				{
					/*std::cout << counter++ << "    " << it.getName() << "    " << it.getMsg() << "     " << "EXPIRED" << std::endl;*/
					status = "EXPIRED";
				}


				std::cout << "| " << std::left << std::setw(2) << counter++
					<< " | " << std::setw(14) << name
					<< " | " << std::setw(14) << msg
					<< " | " << std::setw(9) << status
					<< " |" << std::endl;

			}

			std::cout << "+----+----------------+----------------+------------+" << std::endl;

			getchar();
			
			break;
			//cant delete rn, need to learn thread deletion

			//char ch;
			//std::cout << "Do you want to delete? (Y/N): ";
			//std::cin >> ch;

			//
			//if (ch == 'y' || ch == 'Y')
			//{
			//	int id;
			//	std::cout << "Enter the task to delete: ";
			//	std::cin >> id;

			//	/*if (id > tasks.size() || id < 0)
			//	{
			//		std::cout << "ERROR: CANT DELETE, OUT OF BOUNDS" << std::endl;
			//	}
			//	else
			//	{
			//		tasks.erase(tasks.begin() + (id - 1));
			//	}*/
			//}
			//else
			//	break;

			//system("cls");
		}
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

			auto currTime = std::chrono::system_clock::now();
			if (std::stoi(task_complete) != 1 || (ut.stotp(exe_time) < currTime))
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