/*
	Task Scheduler
	Author: Kushaan Vir Singh
	Personal project for learning C++ multithreading and scheduling.
*/

#include<iostream>
#include <string>
#include<thread>
#include<vector>

#include"task.h"
#include"scheduler.h"
#include"utilities.h"

using namespace std;
using namespace scheduler;

int main()
{
	thread t;
	Sched s;
	utils u;

	while (1)
	{
		u.cleanCUI(); //replace later
		int sel;
		cout << "1.) Add Task" << endl;
		cout << "2.) List All" << endl;
		//cout << "3.) Saves task (Manual)" << endl;
		cout << "3.) Exit" << endl;
		cout << "Input: "; cin >> sel;
		cin.ignore();

		if (sel == 1)
		{
			u.cleanCUI(); //replace later
			string task_name, task_msg, task_time, task_path; int type;
			cout << "Enter Task Name: "; getline(cin, task_name);
			cout << "Enter Task Msg: "; getline(cin, task_msg);
			
			do 
			{
				cout << "Enter Task Time: "; getline(cin, task_time);
				if (!u.isTimeValid(task_time))
					cout << "ERROR: PLEASE ENTER VALID TIME!" << endl;
			} while (!u.isTimeValid(task_time));

			

			cout << "Enter Task Type: "; cin >> type;
			cin.ignore();
			if (type == 2)
			{
				cout << "Enter Path: "; getline(cin, task_path);
			}
			else task_path = "";

			s.newTask(task_name, task_msg, task_time, type, task_path);
		}
		else if (sel == 2)
		{
			s.listAll();

		}
		else if (sel == -1)
		{
			break;
		}
		/*else if (sel == 3)
		{
			s.stop();
			break;
		}*/
		else if( sel == 3/* && s.getTasksSize() != 0*/)
		{
			u.cleanCUI();
			cout << "EXITING!" << endl;
			//dumb implementation, doesnt work, hiding for now
			/*cout << "#----TASK CANVAS----#" << endl;*/
			break;
		}
		else
		{
			break;
		}
	}

	getchar();
}