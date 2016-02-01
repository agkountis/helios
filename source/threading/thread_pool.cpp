#include <iostream>
#include "thread_pool.h"


ThreadPool::~ThreadPool()
{
    terminate();
}

void ThreadPool::wait_and_execute()
{
    std::function<void()> job;

    while (!stop) {

        {
            /**
             * Acquire the mutex.
             */
            std::unique_lock<std::mutex> lock(job_mutex);

            /**
             * The thread waits until jobs exists in the queue.
             */
            has_jobs.wait(lock, [this] {
                return !jobs.empty();
            });

            /**
             * Get the job in the front of the queue.
             */
            job = jobs.front();

            jobs.pop();
        }

        /**
         * Execute the job.
         */
        job();
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

void ThreadPool::terminate()
{
    if(workers.empty()) {
        std::cerr << "Thread pool empty! Can't terminate!" << std::endl;
        return;
    }

    stop = true;

    has_jobs.notify_all();

    for(std::thread &worker : workers) {
        std::cout << "Joining worker " << worker.get_id() << std::endl;
        worker.join();
    }
}

void ThreadPool::add_job(std::function<void()> job)
{
    std::unique_lock<std::mutex> lock(job_mutex);

    jobs.push(job);
}
