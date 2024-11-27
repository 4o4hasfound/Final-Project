#include "Utils/ThreadPool.hpp"

bool ThreadPool::run = false;
std::vector<std::thread> ThreadPool::threads;
std::queue<std::function<void()>> ThreadPool::jobs;
std::mutex ThreadPool::lock;
std::condition_variable ThreadPool::cv;
std::atomic<int> ThreadPool::pendingJobCount = 0;
std::mutex ThreadPool::main_thread;
std::condition_variable ThreadPool::finishAllJob;

void ThreadPool::launch(int numThreads) {
	if (threads.size() >= numThreads) {
		return;
	}
	run = true;
	pendingJobCount = 0;

	for (int i = threads.size(); i < numThreads; ++i) {
		threads.emplace_back(std::thread(&ThreadPool::threadLoop));
	}
}

void ThreadPool::enqueueJob(const std::function<void()>& job) {
	{
		std::unique_lock<std::mutex> unique_lock(lock);
		jobs.push(job);
		pendingJobCount++;
	}
	cv.notify_one();
}

void ThreadPool::waitUntilComplete() {
	if (pendingJobCount <= 0) {
		return;
	}
	std::unique_lock<std::mutex> unique_lock(lock);
	finishAllJob.wait(unique_lock, [] {return pendingJobCount <= 0; });
}

bool ThreadPool::busy() {
	bool isBusy;
	{
		std::unique_lock<std::mutex> unique_lock(lock);
		isBusy = !jobs.empty();
	}
	return isBusy;
}

void ThreadPool::terminate() {
	{
		std::unique_lock<std::mutex> unique_lock(lock);
		run = false;
	}
	cv.notify_all();
	for (std::thread& thread : threads) {
		thread.join();
	}
	threads.clear();
}

int ThreadPool::threadCount() {
	return threads.size();
}

void ThreadPool::threadLoop() {
	while (1) {
		std::function<void()> job;
		{
			std::unique_lock<std::mutex> unique_lock(lock);
			cv.wait(unique_lock, []{
				return !jobs.empty() || !run;
				});
			if (!run && jobs.empty()) {
				return;
			}
			job = std::move(jobs.front());
			jobs.pop();
		}
		job();
		
		if (--pendingJobCount == 0) {
			std::unique_lock<std::mutex> unique_lock(lock);
			finishAllJob.notify_one();
		}
	}
}
