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
	std::chrono::time_point<std::chrono::system_clock>
		utils::stotp(const std::string& time)
	{
		if (time.size() != 16 ||
			time[4] != '-' ||
			time[7] != '-' ||
			time[10] != ' ' ||
			time[13] != ':') {
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

		std::chrono::time_point<std::chrono::system_clock> tp_utc =
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

}