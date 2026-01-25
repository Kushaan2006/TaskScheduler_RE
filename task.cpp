/*
	Task Scheduler
	Author: Kushaan Vir Singh
	Personal project for learning C++ multithreading and scheduling.
*/

#include<iostream>
#include<chrono>
#include<format>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

#include"task.h"
#include"utilities.h"
#include"scheduler.h"

namespace scheduler
{

	std::mutex m;



	utils ut;

	Task::Task(const std::string& task, const std::string& msg, const std::string& time, const int& type, const std::string& path, const int& task_id)
		:m_task_name(task), m_task_msg(msg), m_task_type(type), m_task_complete(0), m_task_id(task_id), m_exe_str_time(time)
	{
		m_exe_path = ut.stoc(path);
		setThreadStatus(0);
		if (time == "")
		{
			m_exe_time = std::chrono::system_clock::now() + std::chrono::seconds(10);
			m_exe_str_time = std::format("{:%Y-%m-%d %H:%M}", m_exe_time);
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
			m_task_complete = 1;
			return;
		}

		std::this_thread::sleep_until(m_exe_time);

		std::lock_guard<std::mutex> lock(m);
		

		if (m_task_type == 1)
		{	
			std::cout << std::endl;
			std::cout << "Task Name: " << m_task_name << std::endl;
			std::cout << "Task Msg : " << m_task_msg << std::endl;
			std::cout << "Task Type: " << m_task_type << std::endl;
			std::cout << "Task Time: " << m_exe_str_time << "UTC" << std::endl;
			/*std::cout << "Task Time: " << format("{:%Y-%m-%d %H:%M:%S}", m_exe_time) << std::endl;*/
			/*std::cout << "EXE  Time: " << format("{:%Y-%m-%d %H:%M:%S}", std::chrono::system_clock::now()) << std::endl;*/
			std::cout << std::endl;
		}
		else if (m_task_type == 2)
		{
			std::cout << std::endl;
			std::cout << "Task Name: " << m_task_name << std::endl;
			std::cout << "Task Msg : " << m_task_msg << std::endl;
			std::cout << "Task Type: " << m_task_type << std::endl;
			std::cout << "Path     : " << m_exe_path << std::endl;
			
			system(m_exe_path);

			//std::string cmd = "cmd /c start \"\" \"" + std::string(m_exe_path) + "\"";
			//system(cmd.c_str());

			std::cout << "Task Time: " << m_exe_str_time << "UTC" << std::endl;
			/*std::cout << "Task Time: " << format("{:%Y-%m-%d %H:%M:%S}", m_exe_time) << std::endl;*/
			/*std::cout << "EXE  Time: " << format("{:%Y-%m-%d %H:%M:%S}", std::chrono::system_clock::now()) << std::endl;*/
			std::cout << std::endl;
		}
		//yet to implement
		/*else if (m_task_type == 3)
		{
			std::cout << std::endl;
			std::cout << "Task Name: " << m_task_name << std::endl;
			std::cout << "Task Msg : " << m_task_msg << std::endl;
			std::cout << "Task Type: " << m_task_type << std::endl;


			std::cout << "Task Time: " << format("{:%Y-%m-%d %H:%M:%S}", m_exe_time) << std::endl;
			std::cout << "EXE  Time: " << format("{:%Y-%m-%d %H:%M:%S}", std::chrono::system_clock::now()) << std::endl;
			std::cout << std::endl;
		}*/

		m_task_complete = 1;

		
	}

	void Task::write(std::ofstream& out) const
	{

		out << m_task_id <<","
			<< m_task_complete << "," 
			<< m_task_name << ","
			<< m_task_msg << "," 
			<< m_exe_path << "," 
			<< m_task_type << "," 
			<< m_exe_str_time << "\n";

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

	/*Task::Task(Task&& obj) noexcept
	{

		this->m_thread_status = std::move(obj.m_thread_status);
		this->m_t = std::move(obj.m_t);
		this->m_task_id = std::move(obj.m_task_id);
		this->m_task_name = std::move(obj.m_task_name);
		this->m_task_msg = std::move(obj.m_task_msg);
		this->m_exe_path = std::move(obj.m_exe_path);
		this->m_task_type = std::move(obj.m_task_type);
		this->m_exe_time = std::move(obj.m_exe_time);
		this->m_exe_str_time = std::move(obj.m_exe_str_time);
		this->m_task_complete = std::move(obj.m_task_complete);
		obj.m_exe_path = nullptr;

	}

	Task& Task::operator=(Task&& obj) noexcept
	{
		if (&obj != this)
		{
			delete[] this->m_exe_path;
			this->m_thread_status = std::move(obj.m_thread_status);
			this->m_t = std::move(obj.m_t);
			this->m_task_id = std::move(obj.m_task_id);
			this->m_task_name = std::move(obj.m_task_name);
			this->m_task_msg = std::move(obj.m_task_msg);
			this->m_exe_path = std::move(obj.m_exe_path);
			this->m_task_type = std::move(obj.m_task_type);
			this->m_exe_time = std::move(obj.m_exe_time);
			this->m_exe_str_time = std::move(obj.m_exe_str_time);
			this->m_task_complete = std::move(obj.m_task_complete);
			obj.m_exe_path = nullptr;
		}

		return *this;
	}*/

	std::string Task::getName() { return m_task_name; }
	std::string Task::getMsg() { return m_task_msg; }
	int Task::getStatus() { return m_task_complete; }
	std::chrono::time_point<std::chrono::system_clock> Task::getTime() { return m_exe_time; }


	Task::~Task()
	{
		delete[] m_exe_path;
	}

}
