
#include<iostream>
#include<chrono>
#include<format>
#include<thread>
#include<mutex>
#include<string>

#include"task.h"
#include"utilities.h"
#include"scheduler.h"

namespace scheduler
{

	std::mutex m;

	utils ut;

	Task::Task(const std::string& task, const std::string& msg, const std::string& time, const int& type)
		:m_task_name(task), m_task_msg(msg), m_task_type(type)
	{
		setThreadStatus(0);
		if (time == "")
		{
			m_exe_time = std::chrono::system_clock::now() + std::chrono::seconds(10);
			std::cout << "Time Rn: " << std::format("{:%Y-%m-%d %H:%M:%S}\n", m_exe_time) << std::endl;

		}
		else
		{
			m_exe_time = ut.stotp(time);
		}
	}

	void Task::exeTask()
	{
		
		setThreadStatus(1);

		if (m_exe_time < std::chrono::system_clock::now())
		{
			std::cout << "Task Expired!" << std::endl;

			return;
		}

		std::this_thread::sleep_until(m_exe_time);

		std::lock_guard<std::mutex> lock(m);
		

		std::cout << std::endl;
		std::cout << "Task Name: " << m_task_name << std::endl;
		std::cout << "Task Msg : " << m_task_msg << std::endl;
		std::cout << "Task Type: " << m_task_type << std::endl;
		std::cout << "Task Time: " << format("{:%Y-%m-%d %H:%M:%S}", m_exe_time) << std::endl;
		std::cout << "EXE  Time: " << format("{:%Y-%m-%d %H:%M:%S}", std::chrono::system_clock::now()) << std::endl;
		std::cout << std::endl;


		
	}

	void Task::setThreadStatus(const int& n)
	{
		m_thread_status = n;
	}

	int Task::getThreadStatus() const
	{
		return m_thread_status;
	}

	void Task::threadIt()
	{
		m_t = std::thread(&Task::exeTask, std::ref(*this));
	}

	void Task::joinIt()
	{
		if (m_t.joinable() /*&& (getThreadStatus() == 1)*/)
		{
			m_t.join();
		}

		setThreadStatus(0);
	}

}
