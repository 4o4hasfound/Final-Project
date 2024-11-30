#pragma once

#include <iostream>
#include "Math/Vector.hpp"

// Enumeration representing different log levels.
enum LogType {
	Info = 0,      // Informational messages.
	Debug = 1,     // Debug messages, usually for development purposes.
	Warning = 2,   // Warning messages, indicating potential issues.
	Error = 3,     // Error messages, for critical problems.
	NoLog = 4      // Disables logging.
};

// Logger class to handle formatted logging based on log levels.
class Logger {
public:
	// Template function for logging messages.
	// - `type`: The log type (e.g., Info, Debug, etc.)
	// - `t`: The first value to log.
	// - `ts`: Additional values to log.
	// - Only enabled if the `type` is not `NoLog`.
	template<LogType type, typename T, typename ... Ts, typename = std::enable_if_t<type != NoLog>>
	static void Log(const T& t, const Ts& ... ts) {
#ifndef DISABLE_LOGGING
		// Skip logging if the current log type is below the configured log level.
		if (type < logLevel) return;

		// Prefix the message based on the log type.
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

	// Overload of Log for cases with no message body.
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

	// Print function for base case with no arguments (ends recursion).
	static void Print() {
		std::cerr << "\n"; // Add a newline to terminate the log message.
	}

	// Template function to handle recursive printing of log message parts.
	template<typename T, typename ... Ts>
	static void Print(const T& t, const Ts& ... ts) {
		std::cerr << t << seperator;
		Print(ts...); // Recursively print the remaining arguments.
	}
};