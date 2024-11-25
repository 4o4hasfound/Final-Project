#include "Utils/Clock.hpp"

Clock::Clock() 
	: m_time(std::chrono::high_resolution_clock::now()) {
}

double Clock::duration() const {
	const auto time = std::chrono::high_resolution_clock::now();
	const double timeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(time - m_time).count();
	return timeDuration;
}

double Clock::reset() {
	const auto time = std::chrono::high_resolution_clock::now();
	const double timeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(time - m_time).count();
	m_time = time;
	return timeDuration;
}
