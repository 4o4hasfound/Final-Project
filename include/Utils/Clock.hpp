#pragma once
#include <chrono>

using Time = std::chrono::high_resolution_clock::time_point;

class Clock {
public:
	Clock();

	// Returns the time passed in milliseconds
	double duration() const;
	// Reset the clock, then returns the time passed in milliseconds
	double reset();
private:
	Time m_time;
};