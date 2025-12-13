#include<iostream>
#include<chrono>

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

		std::chrono::sys_days date{ ymd };

		std::chrono::sys_time<std::chrono::minutes> tp 
			= date + std::chrono::hours{ hour } + std::chrono::minutes{ minute };
		
		return std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp);

	}

}