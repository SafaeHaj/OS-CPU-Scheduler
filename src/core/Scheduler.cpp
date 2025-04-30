#include "Scheduler.h"

void Scheduler::run_simulation() {
    schedule();
    calculate_metrics();
}

void Scheduler::calculate_metrics() {
    float total_waiting = 0, total_turnaround = 0;
    int total_burst = 0;

    for (const auto& p : processes) {
        total_waiting += p.getWaitingTime();
        total_turnaround += p.getTurnaroundTime();
        total_burst += p.getBurstTime();
    }

    metrics.avg_waiting_time = total_waiting / processes.size();
    metrics.avg_turnaround_time = total_turnaround / processes.size();
    metrics.cpu_utilization = (total_burst / static_cast<float>(current_time)) * 100.0f;
}