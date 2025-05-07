#include "core/SJF.h"
#include <algorithm>
#include <iostream>

std::string SJF::getName() const {
    return "Shortest Job First";
}

void SJF::schedule() {
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), 
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });

    // Priority queue for ready processes (sorted by burst time)
    std::priority_queue<Process*, std::vector<Process*>, SJFComparator> pq;
    
    current_time = 0;
    size_t completed = 0;
    size_t total_processes = processes.size();
    size_t idx = 0;

    while (completed != total_processes) {
        // Add arriving processes to the queue
        while (idx < total_processes && processes[idx].getArrivalTime() <= current_time) {
            pq.push(&processes[idx]);
            idx++;
        }

        // If no process is ready, advance time
        if (pq.empty()) {
            if (idx < total_processes) {
                current_time = processes[idx].getArrivalTime();
            }
            continue;
        }

        // Get shortest job
        Process* p = pq.top();
        pq.pop();

        // Update timeline (Gantt chart)
        timeline.emplace_back(p->getId(), current_time, current_time + p->getBurstTime());

        // Calculate process metrics
        p->setCompletionTime(current_time + p->getBurstTime());
        p->setTurnaroundTime(p->getCompletionTime() - p->getArrivalTime());
        p->setWaitingTime(p->getTurnaroundTime() - p->getBurstTime());

        current_time += p->getBurstTime();
        completed++;
    }
}

bool SJF::init() {
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), 
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });
    
    // Clear queue and reset simulation
    while (!ready_queue.empty()) ready_queue.pop();
    
    current_time = 0;
    next_arrival_idx = 0;
    current_process = nullptr;
    simulation_started = true;
    
    // Add processes that arrive at time 0
    while (next_arrival_idx < processes.size() && 
           processes[next_arrival_idx].getArrivalTime() <= current_time) {
        ready_queue.push(&processes[next_arrival_idx]);
        next_arrival_idx++;
    }
    
    // Get the first process if available
    if (!ready_queue.empty()) {
        current_process = ready_queue.top();
        ready_queue.pop();
    }
    
    return true;
}

bool SJF::step() {
    if (!simulation_started) {
        init();
    }
    
    // If all processes are done
    if (next_arrival_idx >= processes.size() && ready_queue.empty() && !current_process) {
        return true; // Simulation complete
    }
    
    // Advance time if no process is ready
    if (!current_process && ready_queue.empty() && next_arrival_idx < processes.size()) {
        current_time = processes[next_arrival_idx].getArrivalTime();
    }
    
    // Add any arriving processes
    while (next_arrival_idx < processes.size() && 
           processes[next_arrival_idx].getArrivalTime() <= current_time) {
        ready_queue.push(&processes[next_arrival_idx]);
        next_arrival_idx++;
    }
    
    // Get next process if needed
    if (!current_process && !ready_queue.empty()) {
        current_process = ready_queue.top();
        ready_queue.pop();
    }
    
    // Process the current job
    if (current_process) {
        current_process->step(1);
        current_time++;
        
        // If process complete, move to next one
        if (current_process->isDone()) {
            // Process complete
            current_process->setCompletionTime(current_time);
            current_process->setTurnaroundTime(current_process->getCompletionTime() - 
                                               current_process->getArrivalTime());
            current_process->setWaitingTime(current_process->getTurnaroundTime() - 
                                            current_process->getBurstTime());
            
            // Get next process
            if (!ready_queue.empty()) {
                current_process = ready_queue.top();
                ready_queue.pop();
            } else {
                current_process = nullptr;
            }
        }
    }
    
    return false; // Simulation not complete yet
}

bool SJF::SJFComparator::operator()(const Process* a, const Process* b) const {
    return a->getRemainingTime() > b->getRemainingTime();
}

void SJF::print_gantt_chart() {
    std::cout << "SJF Gantt Chart:\n";
    for (const auto& entry : timeline) {
        std::cout << "[P" << std::get<0>(entry) << "] "
                  << std::get<1>(entry) << "-" << std::get<2>(entry) << " | ";
    }
    std::cout << "\n";
}
