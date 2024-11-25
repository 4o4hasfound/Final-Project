#pragma once
#include <mutex>
#include <queue>
#include <thread>
#include <atomic>
#include <vector>
#include <functional>
#include <condition_variable>

#include "Debug/Log.hpp"

class ThreadPool {
public:
	static void Launch(int numThreads = std::thread::hardware_concurrency());
	static void EnqueueJob(const std::function<void()>& job);
	static void WaitUntilComplete();
	static bool Busy();
	static void Terminate();

	static int ThreadCount();

	static std::atomic<int> pendingJobCount;
private:
	ThreadPool() = delete;

	static void ThreadLoop();

	static bool run;
	static std::vector<std::thread> threads;
	static std::queue<std::function<void()>> jobs;

	static std::mutex lock;
	static std::condition_variable cv;

	static std::mutex main_thread;
	static std::condition_variable finishAllJob;
};