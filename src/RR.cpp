#include "RR.h"
#include <queue>
#include <algorithm>
#include <iostream>

void RR::schedule() {
    std::queue<Process*> ready_queue;
    std::size_t idx = 0;

    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), 
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });

    current_time = 0;
    while (idx < processes.size() || !ready_queue.empty()) {
        // Add arriving processes to the queue
        while (idx < processes.size() && processes[idx].getArrivalTime() <= current_time) {
            ready_queue.push(&processes[idx]);
            idx++;
        }

        if (ready_queue.empty()) {
            current_time = processes[idx].getArrivalTime();
            continue;
        }

        Process* p = ready_queue.front();
        ready_queue.pop();

        int exec_time = std::min(time_quantum, p->getRemainingTime());
        timeline.emplace_back(p->getId(), current_time, current_time + exec_time);

        // Update remaining time
        p->setRemainingTime(p->getRemainingTime() - exec_time);
        current_time += exec_time;

        // Re-add to queue if not finished
        if (p->getRemainingTime() > 0) {
            ready_queue.push(p);
        } else {
            p->setCompletionTime(current_time);
            p->setTurnaroundTime(p->getCompletionTime() - p->getArrivalTime());
            p->setWaitingTime(p->getTurnaroundTime() - p->getBurstTime());
        }
    }
}

void RR::print_gantt_chart() {
    std::cout << "Round Robin Gantt Chart (Time Quantum = " << time_quantum << "):\n";
    for (const auto& entry : timeline) {
        std::cout << "[P" << std::get<0>(entry) << "] "
                  << std::get<1>(entry) << "-" << std::get<2>(entry) << " | ";
    }
    std::cout << "\n";
}