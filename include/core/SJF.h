#pragma once
#include "Scheduler.h"
#include <queue>

class SJF : public Scheduler {
private:
    // Comparator for the priority queue (shorter burst time has higher priority)
    struct SJFComparator {
        bool operator()(const Process* a, const Process* b) const {
            return a->getRemainingTime() > b->getRemainingTime();
        }
    };

    std::priority_queue<Process*, std::vector<Process*>, SJFComparator> ready_queue;
    Process* current_process = nullptr;
    size_t next_arrival_idx = 0;
    bool simulation_started = false;

public:
    std::string getName() const override { return "Shortest Job First"; }
    void schedule() override;
    void print_gantt_chart() override;
    
    // Step-by-step simulation support
    bool init() override;
    bool step() override;
};