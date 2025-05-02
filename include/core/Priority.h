#pragma once
#include "Scheduler.h"
#include <queue>

class Priority : public Scheduler {
private:
    // Comparator for the priority queue (lower priority number = higher priority)
    struct PriorityComparator {
        bool operator()(const Process* a, const Process* b) const {
            return a->getPriority() > b->getPriority();
        }
    };

    std::priority_queue<Process*, std::vector<Process*>, PriorityComparator> ready_queue;
    Process* current_process = nullptr;
    size_t next_arrival_idx = 0;
    bool simulation_started = false;

public:
    std::string getName() const override { return "Priority Scheduling"; }
    void schedule() override;
    void print_gantt_chart() override;
    
    // Step-by-step simulation support
    bool init() override;
    bool step() override;
};