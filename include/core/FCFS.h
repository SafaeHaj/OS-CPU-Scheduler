#pragma once
#include "Scheduler.h"

class FCFS : public Scheduler {
private:
    size_t current_process_idx = 0;
    bool simulation_started = false;
    Process* current_process = nullptr;

public:
    std::string getName() const override { return "First Come First Served"; }
    void schedule() override;
    void print_gantt_chart() override;
    
    bool init() override;
    bool step() override;
};