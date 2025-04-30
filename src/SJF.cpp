#include "SJF.h"
#include <algorithm>
#include <iostream>
#include <vector>

void SJF::schedule() {
    // Sort by arrival time first
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    current_time = 0;
    std::vector<Process*> available;

    size_t idx = 0;
    while (idx < processes.size() || !available.empty()) {
        // Add newly arrived processes
        while (idx < processes.size() && processes[idx].getArrivalTime() <= current_time) {
            available.push_back(&processes[idx]);
            idx++;
        }

        if (available.empty()) {
            current_time = processes[idx].getArrivalTime();
            continue;
        }

        // Find the shortest job
        auto shortest = std::min_element(available.begin(), available.end(),
            [](const Process* a, const Process* b) {
                return a->getBurstTime() < b->getBurstTime();
            });

        Process* p = *shortest;
        available.erase(shortest);

        // Execute the process
        timeline.emplace_back(p->getId(), current_time, current_time + p->getBurstTime());
        current_time += p->getBurstTime();
        p->setCompletionTime(current_time);
        p->setTurnaroundTime(p->getCompletionTime() - p->getArrivalTime());
        p->setWaitingTime(p->getTurnaroundTime() - p->getBurstTime());
    }
}

void SJF::print_gantt_chart() {
    std::cout << "SJF Gantt Chart:\n";
    for (const auto& entry : timeline) {
        std::cout << "[P" << std::get<0>(entry) << "] "
                  << std::get<1>(entry) << "-" << std::get<2>(entry) << " | ";
    }
    std::cout << "\n";
}