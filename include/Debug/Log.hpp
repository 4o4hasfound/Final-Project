#pragma once
#include <iostream>

#include "Math/Vector.hpp"

enum LogType {
	Info = 0,
	Debug = 1,
	Warning = 2,
	Error = 3,

	NoLog = 4
};


class Logger {
public:
	template<LogType type, typename T, typename ... Ts, typename = std::enable_if_t<type != NoLog>>
	static void Log(const T& t, const Ts& ... ts) {
#ifndef DISABLE_LOGGING
		if (type < logLevel) return;

		switch (type) {
		case Info:
			std::cerr << "Info: ";
			break;
		case Debug: 
			std::cerr << "Debug: ";
			break;
		case Warning:
			std::cerr << "Warning: ";
			break;
		case Error:
			std::cerr << "Error: ";
			break;
		}
		Print(t, ts...);
#endif
	}

	template<LogType type, typename = std::enable_if_t<type != NoLog>>
	static void Log() {
#ifndef DISABLE_LOGGING
		Print();
#endif
	}

	static LogType logLevel;
	static std::string seperator;
private:
	Logger() = delete;

	static void Print() {
		std::cerr << "\n";
	}

	template<typename T, typename ... Ts>
	static void Print(const T& t, const Ts& ... ts) {
		std::cerr << t << seperator;
		Print(ts...);
	}
};