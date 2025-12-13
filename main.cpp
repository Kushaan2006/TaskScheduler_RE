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

	while (1)
	{
		system("cls"); //replace later
		int sel;
		cout << "1.) Add Task" << endl;
		cout << "2.) Exit" << endl;
		cout << "Input: "; cin >> sel;
		cin.ignore();

		if (sel == 1)
		{
			system("cls"); //replace later
			string task_name, task_msg, task_time, task_path; int type;
			cout << "Enter Task Name: "; getline(cin, task_name);
			cout << "Enter Task Msg: "; getline(cin, task_msg);
			cout << "Enter Task Time: "; getline(cin, task_time);
			cout << "Enter Task Type: "; cin >> type;
			cin.ignore();
			if (type == 2)
			{
				cout << "Enter Path: "; getline(cin, task_path);
			}
			else task_path = "";

			s.newTask(task_name, task_msg, task_time, type, task_path);
		}
		else if (sel == -1)
		{
			break;
		}
		else
		{
			system("cls");
			cout << "#----TASK CANVAS----#" << endl;
			break;
		}
	}

	
}