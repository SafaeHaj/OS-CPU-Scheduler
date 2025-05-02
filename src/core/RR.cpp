#include "core/RR.h"
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

bool RR::init() {
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), 
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });
    
    // Clear queue
    std::queue<Process*> empty;
    std::swap(ready_queue, empty);
    
    current_time = 0;
    next_arrival_idx = 0;
    current_process = nullptr;
    quantum_used = 0;
    
    // Add processes that arrive at time 0
    while (next_arrival_idx < processes.size() && 
           processes[next_arrival_idx].getArrivalTime() <= current_time) {
        ready_queue.push(&processes[next_arrival_idx]);
        next_arrival_idx++;
    }
    
    // Get the first process if available
    if (!ready_queue.empty()) {
        current_process = ready_queue.front();
        ready_queue.pop();
    }
    
    return true;
}

bool RR::step() {
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
        current_process = ready_queue.front();
        ready_queue.pop();
        quantum_used = 0;
    }
    
    // Process the current job
    if (current_process) {
        current_process->step(1);
        current_time++;
        quantum_used++;
        
        // Check if time slice exhausted or process complete
        if (current_process->isDone() || quantum_used >= time_quantum) {
            if (current_process->isDone()) {
                // Process complete
                current_process->setCompletionTime(current_time);
                current_process->setTurnaroundTime(current_process->getCompletionTime() - 
                                                   current_process->getArrivalTime());
                current_process->setWaitingTime(current_process->getTurnaroundTime() - 
                                                current_process->getBurstTime());
            } else {
                // Time slice exhausted, put back in queue
                ready_queue.push(current_process);
            }
            
            // Get next process
            if (!ready_queue.empty()) {
                current_process = ready_queue.front();
                ready_queue.pop();
                quantum_used = 0;
            } else {
                current_process = nullptr;
            }
        }
    }
    
    return false; // Simulation not complete yet
}

void RR::print_gantt_chart() {
    std::cout << "Round Robin Gantt Chart (Time Quantum = " << time_quantum << "):\n";
    for (const auto& entry : timeline) {
        std::cout << "[P" << std::get<0>(entry) << "] "
                  << std::get<1>(entry) << "-" << std::get<2>(entry) << " | ";
    }
    std::cout << "\n";
}