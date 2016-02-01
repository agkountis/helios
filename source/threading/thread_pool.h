#ifndef HELIOS_THREAD_POOL_H
#define HELIOS_THREAD_POOL_H

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool {
private:
    std::vector<std::thread> workers;

    std::queue< std::function<void()> > jobs;

    std::mutex job_mutex;

    std::condition_variable has_jobs;

    bool stop = false;

    void wait_and_execute();

public:
    bool initialize();

    void terminate();

    void add_job(std::function<void()> job);
};

#endif //HELIOS_THREAD_POOL_H
