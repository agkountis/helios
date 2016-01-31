#ifndef HELIOS_JOB_H
#define HELIOS_JOB_H

#include <thread>
#include <vector>
#include <queue>

class ThreadPool {
private:
    std::vector<std::thread> workers;

    std::queue< std::function<void()> > jobs;

public:
    bool initialize();
};

#endif //HELIOS_JOB_H
