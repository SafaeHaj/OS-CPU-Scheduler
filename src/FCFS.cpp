#include "FCFS.h"
#include <algorithm>
#include <iostream>


void FCFS::schedule() {
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), 
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });

    current_time = 0;
    for (auto& p : processes) {
        // Handle idle time if no process is ready
        if (current_time < p.getArrivalTime()) {
            current_time = p.getArrivalTime();
        }

        // Update timeline (Gantt chart)
        timeline.emplace_back(p.getId(), current_time, current_time + p.getBurstTime());

        // Calculate process metrics
        p.setCompletionTime(current_time + p.getBurstTime());
        p.setTurnaroundTime(p.getCompletionTime() - p.getArrivalTime());
        p.setWaitingTime(p.getTurnaroundTime() - p.getBurstTime());

        current_time += p.getBurstTime();
    }
}

void FCFS::print_gantt_chart() {
    std::cout << "FCFS Gantt Chart:\n";
    for (const auto& entry : timeline) {
        std::cout << "[P" << std::get<0>(entry) << "] "
                  << std::get<1>(entry) << "-" << std::get<2>(entry) << " | ";
    }
    std::cout << "\n";
}


































