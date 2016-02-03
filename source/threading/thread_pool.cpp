#include <iostream>
#include "thread_pool.h"


ThreadPool::~ThreadPool()
{
    terminate();
}

void ThreadPool::wait_and_execute()
{
    std::function<void()> job;

    while (true) {

        {
            /**
             * Acquire the mutex.
             */
            std::unique_lock<std::mutex> lock(job_mutex);

            /**
             * The thread waits until jobs exists in the queue.
             */
            has_jobs.wait(lock, [this] {
                return !jobs.empty() || stop;
            });

            if(stop) {
                std::cout << "Stopping" << std::endl;
                return;
            }

            /**
             * Get the job in the front of the queue.
             */
            job = jobs.front();

            jobs.pop();

            ++active_jobs;
        }

        /**
         * Execute the job.
         */
        job();

        {
            std::unique_lock<std::mutex> lock(job_mutex);

            --active_jobs;

            if(jobs.empty())
                jobs_done.notify_all();
        }
    }

}

bool ThreadPool::initialize()
{
    std::cout << "Initializing thread pool..." << std::endl;

    /**
     * Get the system's supported thread count.
     */
    int thread_count = std::thread::hardware_concurrency();

    if (!thread_count) {
        std::cerr << "Not able to detect the system's available thread count!" << std::endl;
        return false;
    }

    std::cout << "Available system threads: " << thread_count << std::endl;

    std::cout << "Creating workers..." << std::endl;

    /**
     * Spawn the worker threads.
     */
    for (int i = 0; i < thread_count; i++) {

        /**
         * The workers will execute an infinite loop function
         * and will wait for a job to enter the job queue. Once a job is in the the queue
         * the threads will wake up to acquire and execute it.
         */
        workers.emplace_back(&ThreadPool::wait_and_execute, this);
    }

    return true;
}


void ThreadPool::wait()
{
    std::unique_lock<std::mutex> lock(job_mutex);

    jobs_done.wait(lock, [this] {
       return jobs.empty() && active_jobs == 0;
    });
}

void ThreadPool::terminate()
{
    if(workers.empty())
        return;

    {
        std::unique_lock<std::mutex> lock(job_mutex);

        if(!jobs.empty()) {
            for(size_t i = 0; i < jobs.size(); i++) {
                jobs.pop();
            }
        }

        stop = true;

        has_jobs.notify_all();
    }

    for(auto &worker : workers) {
        worker.join();
    }
}

void ThreadPool::add_job(std::function<void()> job)
{
    std::unique_lock<std::mutex> lock(job_mutex);

    jobs.push(job);

    has_jobs.notify_one();
}


size_t ThreadPool::queued_job_count() const
{
    std::unique_lock<std::mutex> lock(job_mutex);

    return jobs.size();
}

size_t ThreadPool::active_job_count() const
{
    std::unique_lock<std::mutex> lock(job_mutex);

    return active_jobs;
}


size_t ThreadPool::pending_job_count() const
{
    std::unique_lock<std::mutex> lock(job_mutex);

    return active_jobs + jobs.size();
}
