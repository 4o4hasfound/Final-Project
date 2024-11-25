#pragma once
#include <random>
#include <ctime>
#include <limits>

class Random {
public:
	Random() = delete;

	template<typename T = int>
	static T GetInt();
	template<typename T = int>
	static T GetInt(T end);
	template<typename T = int>
	static T GetInt(T start, T end);

	template<typename T = float>
	static T GetReal();
	template<typename T = float>
	static T GetReal(T end);
	template<typename T = float>
	static T GetReal(T start, T end);
};

template<typename T>
inline T Random::GetInt() {
	std::mt19937 generator(std::random_device{}());
	std::uniform_int_distribution<T> uniform(0, std::numeric_limits<T>::max());
	return uniform(generator);
}

template<typename T>
inline T Random::GetInt(T end) {
	std::mt19937 generator(std::random_device{}());
	std::uniform_int_distribution<T> uniform(0, end);
	return uniform(generator);
}

template<typename T>
inline T Random::GetInt(T start, T end) {
	std::mt19937 generator(std::random_device{}());
	std::uniform_int_distribution<T> uniform(start, end);
	return uniform(generator);
}

template<typename T>
inline T Random::GetReal() {
	std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<T> uniform(0, std::numeric_limits<T>::max());
	return uniform(generator);
}

template<typename T>
inline T Random::GetReal(T end) {
	std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<T> uniform(0, end);
	return uniform(generator);
}

template<typename T>
inline T Random::GetReal(T start, T end) {
	std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<T> uniform(start, end);
	return uniform(generator);
}