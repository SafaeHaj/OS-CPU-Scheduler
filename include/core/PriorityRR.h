#pragma once
#include "Scheduler.h"
#include <queue>
#include <vector>
#include <map>

class PriorityRR : public Scheduler {
private:
    int time_quantum;
    std::map<int, std::queue<Process*>> priority_queues; // Priority level -> queue
    int current_priority = -1;
    Process* current_process = nullptr;
    int quantum_used = 0;
    size_t next_arrival_idx = 0;
    bool simulation_started = false;
    
    // Helper method to find the highest priority with ready processes
    int findHighestPriorityQueue() const;

public:
    PriorityRR(int quantum) : time_quantum(quantum) {}
    
    std::string getName() const override { 
        return "Priority Round Robin (TQ=" + std::to_string(time_quantum) + ")"; 
    }
    
    void schedule() override;
    void print_gantt_chart() override;
    
    // Step-by-step simulation support
    bool init() override;
    bool step() override;
};