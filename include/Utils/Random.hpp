#pragma once
#include <random>
#include <ctime>
#include <limits>

class Random {
public:
	Random() = delete;

	// type char, short, int, long, long long
	template<typename T = int>
	static T getInt();
	template<typename T = int>
	static T getInt(T end);
	template<typename T = int>
	static T getInt(T start, T end);

	// type float, double, long double
	template<typename T = float>
	static T getReal();
	template<typename T = float>
	static T getReal(T end);
	template<typename T = float>
	static T getReal(T start, T end);
};

template<typename T>
inline T Random::getInt() {
	std::mt19937 generator(std::random_device{}());
	std::uniform_int_distribution<T> uniform(0, std::numeric_limits<T>::max());
	return uniform(generator);
}

template<typename T>
inline T Random::getInt(T end) {
	std::mt19937 generator(std::random_device{}());
	std::uniform_int_distribution<T> uniform(0, end);
	return uniform(generator);
}

template<typename T>
inline T Random::getInt(T start, T end) {
	std::mt19937 generator(std::random_device{}());
	std::uniform_int_distribution<T> uniform(start, end);
	return uniform(generator);
}

template<typename T>
inline T Random::getReal() {
	std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<T> uniform(0, std::numeric_limits<T>::max());
	return uniform(generator);
}

template<typename T>
inline T Random::getReal(T end) {
	std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<T> uniform(0, end);
	return uniform(generator);
}

template<typename T>
inline T Random::getReal(T start, T end) {
	std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<T> uniform(start, end);
	return uniform(generator);
}