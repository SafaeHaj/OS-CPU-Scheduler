#include "core/RR.h"
#include <algorithm>
#include <iostream>

RR::RR(int quantum) : time_quantum(quantum) {}
std::string RR::getName() const {
    return "Round Robin (TQ=" + std::to_string(time_quantum) + ")";
}

bool RR::init() {
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
