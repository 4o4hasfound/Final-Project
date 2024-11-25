#pragma once
#include <chrono>

class Clock {
public:
	Clock();

	double duration() const;
	double reset();
private:
	std::chrono::high_resolution_clock::time_point m_time;
};