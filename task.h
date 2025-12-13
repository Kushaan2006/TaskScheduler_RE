#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include<iostream>
#include<chrono>


namespace scheduler
{
	class Task
	{
		int m_thread_status{};
		std::thread m_t{};

		std::string m_task_name{};
		std::string m_task_msg{};
		char* m_exe_path{};
		int m_task_type{};

		std::chrono::time_point<std::chrono::system_clock> m_exe_time;

	public:

		void exeTask();

		Task(
			const std::string& task = "!!NO TASK!!",
			const std::string& msg = "!!NO MSG!!",
			const std::string& time = "",
			const int& type = 1,
			const std::string& path = ""
		);

		Task(Task& obj) = delete;
		Task& operator=(Task& obj) = delete;

		Task(Task&& obj) noexcept;
		Task& operator=(Task&& obj) noexcept;


		void setThreadStatus(const int& n = 0);

		int getThreadStatus() const;
		void threadIt();

		void joinIt();

		~Task();
	};
}

#endif // !TASK_SCHEDULER_H
