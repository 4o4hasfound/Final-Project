#pragma once
#include <chrono>

class Clock {
public:
	Clock();

	// Returns the time passed in milliseconds
	double duration() const;
	// Reset the clock, then returns the time passed in milliseconds
	double reset();
private:
	std::chrono::high_resolution_clock::time_point m_time;
};