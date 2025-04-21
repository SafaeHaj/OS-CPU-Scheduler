#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <tuple>
#include "Process.h"



class Scheduler {
public:
    virtual ~Scheduler() = default;
    virtual void simulate(std::vector<Process>& processes) = 0;
    
    // Stores timeline as (process_id, start_time, end_time)
    std::vector<std::tuple<int, int, int>> timeline;

protected:
    void updateTimeline(int pid, int start, int end) {
        timeline.emplace_back(pid, start, end);
    }
};

#endif // SCHEDULER_H