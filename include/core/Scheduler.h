#pragma once
#include <vector>
#include <string>
#include "Process.h"

struct Metrics {
    float avg_waiting_time = 0.0f;
    float avg_turnaround_time = 0.0f;
    float cpu_utilization = 0.0f;
    int total_idle_time = 0;
};

class Scheduler {
protected:
    std::vector<std::tuple<int, int, int>> timeline; // (ID, start, end)
    int current_time = 0;

public:
    Metrics metrics;
    std::vector<Process> processes;
    
    virtual ~Scheduler() = default;
    virtual std::string getName() const = 0;
    virtual void schedule() = 0;
    virtual void print_gantt_chart() = 0;
    
    virtual bool step() = 0;  // Return true if simulation is complete
    virtual bool init() = 0;  // Initialize the simulation
    
    void run_simulation();
    void calculate_metrics();
};