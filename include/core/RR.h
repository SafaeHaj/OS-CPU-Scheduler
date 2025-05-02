#pragma once
#include "Scheduler.h"
#include <queue>

class RR : public Scheduler {
private:
    int time_quantum;
    std::queue<Process*> ready_queue;
    Process* current_process = nullptr;
    int quantum_used = 0;
    size_t next_arrival_idx = 0;

public:
    RR(int quantum) : time_quantum(quantum) {}
    
    std::string getName() const override { return "Round Robin (TQ=" + std::to_string(time_quantum) + ")"; }
    void schedule() override;
    void print_gantt_chart() override;
    
    bool init() override;
    bool step() override;
};