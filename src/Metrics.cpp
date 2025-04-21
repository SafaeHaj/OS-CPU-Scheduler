#include "Metrics.h"
#include <iostream>
#include <numeric>

void Metrics::printGanttChart(const std::vector<std::tuple<int, int, int>>& timeline) {
    std::cout << "\nGantt Chart:\n";
    for (const auto& [pid, start, end] : timeline) {
        std::cout << "P" << pid << " [" << start << "-" << end << "] ";
    }
    std::cout << "\n\n";
}

void Metrics::calculateMetrics(const std::vector<Process>& processes) {
    double total_waiting = 0;
    double total_turnaround = 0;
    int total_burst = 0;
    int max_completion = 0;

    for (const auto& p : processes) {
        total_waiting += p.waiting_time;
        total_turnaround += p.turnaround_time;
        total_burst += p.burst_time;
        max_completion = std::max(max_completion, p.completion_time);
    }

    std::cout << "Average Waiting Time: " 
              << total_waiting / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " 
              << total_turnaround / processes.size() << "\n";
    std::cout << "CPU Utilization: " 
              << (static_cast<double>(total_burst) / max_completion) * 100 
              << "%\n";
}