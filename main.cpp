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
			string task_name, task_msg, task_time; int type;
			cout << "Enter Task Name: "; getline(cin, task_name);
			cout << "Enter Task Msg: "; getline(cin, task_msg);
			cout << "Enter Task Time: "; getline(cin, task_time);
			cout << "Enter Task Type: "; cin >> type;
			cin.ignore();

			s.newTask(task_name, task_msg, task_time, type);
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