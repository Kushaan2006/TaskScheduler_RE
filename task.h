/*
	Task Scheduler
	Author: Kushaan Vir Singh
	Personal project for learning C++ multithreading and scheduling.
*/


#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include<iostream>
#include<chrono>
#include<fstream>
#include<string>
#include <thread>

//#include"scheduler.h"

namespace scheduler
{
	class Task
	{
		int m_thread_status{};
		int m_task_complete{};
		int m_task_id{};
		std::thread m_t{};

		std::string m_task_name{};
		std::string m_task_msg{};
		char* m_exe_path{};
		int m_task_type{};

		std::string m_exe_str_time;
		std::chrono::time_point<std::chrono::system_clock> m_exe_time;

	public:

		void exeTask();

		Task(
			const std::string& task = "!!NO TASK!!",
			const std::string& msg = "!!NO MSG!!",
			const std::string& time = "",
			const int& type = 1,
			const std::string& path = "" ,
			const int& task_id=-1
		);

		Task(Task& obj) = delete;
		Task& operator=(Task& obj) = delete;

		Task(Task&& obj) noexcept;
		Task& operator=(Task&& obj) noexcept;

		std::string getName() { return m_task_name; }
		std::string getMsg() { return m_task_msg;  }
		int getStatus() { return m_task_complete;  }
		auto getTime() { return m_exe_time;  }

		void setThreadStatus(const int& n = 0);

		int getThreadStatus() const;
		void threadIt();

		void joinIt();
		
		void write(std::ofstream& obj) const;

		~Task();
	};
}

#endif // !TASK_SCHEDULER_H
