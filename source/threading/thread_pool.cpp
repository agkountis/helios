#include <iostream>
#include "thread_pool.h"


bool ThreadPool::initialize()
{
    std::cout << "Initializing thread pool..." <<std::endl;

    /**
     * Get the system's supported thread count.
     */
    unsigned int thread_count = std::thread::hardware_concurrency();

    if (!thread_count) {
        std::cerr << "Not able to detect the system's available thread count!" << std::endl;
        return false;
    }

    std::cout << "Available system threads: " << thread_count << std::endl;

    return true;
}
