#include "PriorityRR.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <vector>

void PriorityRR::schedule() {
    // Sort processes by priority and arrival time
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        if (a.getPriority() != b.getPriority())
            return a.getPriority() < b.getPriority(); // Lower priority number first
        return a.getArrivalTime() < b.getArrivalTime();
    });

    current_time = 0;
    size_t idx = 0;

    while (idx < processes.size()) {
        int current_priority = processes[idx].getPriority();
        std::queue<Process*> rr_queue;

        // Collect all processes with current_priority
        while (idx < processes.size() && processes[idx].getPriority() == current_priority) {
            rr_queue.push(&processes[idx]);
            idx++;
        }

        // Process this priority group with RR
        while (!rr_queue.empty()) {
            Process* p = rr_queue.front();
            rr_queue.pop();

            // Handle arrival time
            if (current_time < p->getArrivalTime()) {
                current_time = p->getArrivalTime();
            }

            int exec_time = std::min(time_quantum, p->getRemainingTime());
            timeline.emplace_back(p->getId(), current_time, current_time + exec_time);
            p->setRemainingTime(p->getRemainingTime() - exec_time);
            current_time += exec_time;

            if (p->getRemainingTime() > 0) {
                rr_queue.push(p);
            } else {
                p->setCompletionTime(current_time);
                p->setTurnaroundTime(p->getCompletionTime() - p->getArrivalTime());
                p->setWaitingTime(p->getTurnaroundTime() - p->getBurstTime());
            }
        }
    }
}

void PriorityRR::print_gantt_chart() {
    std::cout << "Priority + RR Gantt Chart (Quantum=" << time_quantum << "):\n";
    for (const auto& entry : timeline) {
        std::cout << "[P" << std::get<0>(entry) << "] "
                  << std::get<1>(entry) << "-" << std::get<2>(entry) << " | ";
    }
    std::cout << "\n";
}