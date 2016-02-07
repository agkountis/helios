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

    mutable std::mutex job_mutex;

    std::condition_variable has_jobs;

    std::condition_variable jobs_done;

    bool stop = false;

    size_t active_jobs = 0;

    void wait_and_execute();

public:

    ~ThreadPool();

    bool initialize();

    void wait();

    void terminate();

    void add_job(std::function<void()> job);

    void add_jobs(const std::vector< std::function<void()> > &jobs);

    size_t queued_job_count() const;

    size_t active_job_count() const;

    size_t pending_job_count() const;
};

#endif //HELIOS_THREAD_POOL_H
