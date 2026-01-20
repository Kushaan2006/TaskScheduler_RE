/*
	Task Scheduler
	Author: Kushaan Vir Singh
	Personal project for learning C++ multithreading and scheduling.
*/


#include<iostream>
#include<chrono>
#include<string>

#include"utilities.h"

namespace scheduler
{

	void utils::cleanCUI()
	{
		#if defined(_WIN32) || defined(_WIN64)
		system("cls");
        #elif defined(__linux__)
		system("clear");
        #else
		cout << std::endl << std::endl;
        #endif
	}

	std::chrono::time_point<std::chrono::system_clock>
		utils::stotp(const std::string& time)
	{
		std::chrono::time_point<std::chrono::system_clock> tp_utc;

		if (time.size() != 16 ||
			time[4] != '-' ||
			time[7] != '-' ||
			time[10] != ' ' ||
			time[13] != ':') 
		{
		/*	tp_utc = std::chrono::system_clock::now() + std::chrono::seconds(10);*/
			throw std::invalid_argument("stotp: invalid format (expected YYYY-MM-DD HH:MM)");
		}


		//012345678910 11 12 13 14 15
		//YYYY-MM-DD   H  H  -  M  M
		int year = std::stoi(time.substr(0,4));
		int month = std::stoi(time.substr(5,2));
		int day = std::stoi(time.substr(8,2));
		int hour = std::stoi(time.substr(11,2));
		int minute = std::stoi(time.substr(14,2));

		if (month < 1 || month > 12 ||
			day < 1 || day   > 31 ||
			hour < 0 || hour  > 23 ||
			minute < 0 || minute> 59) {
			throw std::invalid_argument("stotp: value out of range");
		}

		std::chrono::year_month_day ymd{
			std::chrono::year {year}, 
			std::chrono::month { static_cast<unsigned>(month) }, 
			std::chrono::day{ static_cast<unsigned>(day) } };

		/*std::chrono::sys_days date{ ymd };

		std::chrono::sys_time<std::chrono::minutes> tp 
			= date + std::chrono::hours{ hour } + std::chrono::minutes{ minute };

		auto tz = std::chrono::current_zone();
		std::chrono::zoned_time local_zt{ tz, tp };

		std::chrono::sys_time<std::chrono::minutes> tp_utc =
			std::chrono::floor<std::chrono::minutes>(local_zt.get_sys_time());


		
		return std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp_utc);*/


		//converting local time to utc
		std::chrono::local_days date{ ymd };

		std::chrono::local_time<std::chrono::minutes> local_tp
			= date + std::chrono::hours{ hour } + std::chrono::minutes{ minute };

		const std::chrono::time_zone* tz = std::chrono::current_zone();
		std::chrono::zoned_time local_zt{ tz, local_tp };

		tp_utc =
			std::chrono::floor<std::chrono::system_clock::duration>( local_zt.get_sys_time());

		return tp_utc;

	}

	char* utils::stoc(const std::string& str) const
	{
		char* path = new char[str.length() + 1];
		int i = 0;
		for (auto ch : str)
		{
			path[i++] = ch;
		}
		path[str.length()] = '\0';
		return path;
	}

	bool utils::isLeapYear(const int& yr)
	{
		if (yr % 400 == 0) return true;
		if (yr % 100 == 0) return false;
		return (yr % 4 == 0);
	}

	bool utils::isTimeValid(const std::string& str)
	{
		if (str.empty()) return true;


		if (str.length() != 16)
			return false;

		// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		// Y Y Y Y - M M - D D    H  H  :  M  M
		if (str[4] != '-' || str[7] != '-' || str[10] != ' ' || str[13] != ':')
			return false;

		try
		{
			int Y = stoi(str.substr(0, 4));
			int MON = stoi(str.substr(5, 2));
			int D = stoi(str.substr(8, 2));
			int H = stoi(str.substr(11, 2));
			int MIN = stoi(str.substr(14, 2));

			if (Y < 1)            return false;
			if (MON < 1 || MON > 12)  return false;

			//check leap year
			if (MON == 2)
			{
				if (D < 1) return false;
				if (isLeapYear(Y) && D > 29) return false;
				if (!isLeapYear(Y) && D > 28) return false;
			}
			
			//check 31 jan - july
			if (MON != 2 && MON < 8 && (MON % 2 != 0))
			{
				if (D < 1 || D > 31) return false;
			}
			
			//check 31 aug - dec
			if (MON > 7 && (MON % 2 == 0))
			{
				if (D < 1 || D > 31) return false;
			}

			if (MON != 2)
			{
				if (!((MON != 2 && MON < 8 && (MON % 2 != 0)) || (MON > 7 && (MON % 2 == 0))))
				{
					if (D < 1 || D > 30) return false;
				}
			}

			if (H < 0 || H > 23) return false;
			if (MIN < 0 || MIN > 59) return false;

		}
		catch (...)
		{
			return false;
		}

		return true;

	}

}