#include "core/PriorityRR.h"
#include <algorithm>
#include <iostream>
#include <limits>

PriorityRR::PriorityRR(int quantum) : time_quantum(quantum) {}

std::string PriorityRR::getName() const {
    return "Priority Round Robin (TQ=" + std::to_string(time_quantum) + ")";
}

void PriorityRR::schedule() {
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), 
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });

    // Map from priority level to queue of processes with that priority
    std::map<int, std::queue<Process*>> priority_queues;
    size_t completed = 0;
    size_t total_processes = processes.size();
    size_t idx = 0;
    
    current_time = 0;
    
    while (completed != total_processes) {
        // Add arriving processes to the appropriate priority queue
        while (idx < total_processes && processes[idx].getArrivalTime() <= current_time) {
            int priority = processes[idx].getPriority();
            priority_queues[priority].push(&processes[idx]);
            idx++;
        }
        

        // If no process is ready, advance time
        if (std::all_of(priority_queues.begin(), priority_queues.end(),
                        [](const auto& pair) { return pair.second.empty(); })) {
            if (idx < total_processes) {
                current_time = processes[idx].getArrivalTime();
            }
            continue;
        }

        // Find highest priority non-empty queue
        int highest_priority = std::numeric_limits<int>::max();
        for (const auto& pair : priority_queues) {
            if (!pair.second.empty() && pair.first < highest_priority) {
                highest_priority = pair.first;
            }
        }

        // Execute processes in RR fashion within the priority level
        std::queue<Process*>& current_queue = priority_queues[highest_priority];
        Process* p = current_queue.front();
        current_queue.pop();
        
        int exec_time = std::min(time_quantum, p->getRemainingTime());
        timeline.emplace_back(p->getId(), current_time, current_time + exec_time);
        
        p->setRemainingTime(p->getRemainingTime() - exec_time);
        current_time += exec_time;
        
        // Re-add to queue if not finished
        if (p->getRemainingTime() > 0) {
            // Check if any higher priority processes arrived during execution
            bool higher_priority_arrived = false;
            for (int prio = 0; prio < highest_priority; ++prio) {
                if (!priority_queues[prio].empty()) {
                    higher_priority_arrived = true;
                    break;
                }
            }
            
            // Add back to appropriate queue
            if (!higher_priority_arrived) {
                current_queue.push(p);
            } else {
                priority_queues[highest_priority].push(p);
            }
        } else {
            // Process is complete
            p->setCompletionTime(current_time);
            p->setTurnaroundTime(p->getCompletionTime() - p->getArrivalTime());
            p->setWaitingTime(p->getTurnaroundTime() - p->getBurstTime());
            completed++;
        }
    }
}

int PriorityRR::findHighestPriorityQueue() const {
    int highest_priority = std::numeric_limits<int>::max();
    for (const auto& pair : priority_queues) {
        if (!pair.second.empty() && pair.first < highest_priority) {
            highest_priority = pair.first;
        }
    }
    
    return (highest_priority == std::numeric_limits<int>::max()) ? -1 : highest_priority;
}

bool PriorityRR::init() {
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), 
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });
    
    // Clear queues
    priority_queues.clear();
    
    current_time = 0;
    next_arrival_idx = 0;
    current_process = nullptr;
    quantum_used = 0;
    current_priority = -1;
    simulation_started = true;
    
    // Add processes that arrive at time 0
    while (next_arrival_idx < processes.size() && 
           processes[next_arrival_idx].getArrivalTime() <= current_time) {
        int prio = processes[next_arrival_idx].getPriority();
        priority_queues[prio].push(&processes[next_arrival_idx]);
        next_arrival_idx++;
    }
    
    // Get the first process if available
    current_priority = findHighestPriorityQueue();
    if (current_priority != -1) {
        current_process = priority_queues[current_priority].front();
        priority_queues[current_priority].pop();
    }
    
    return true;
}

bool PriorityRR::step() {
    if (!simulation_started) {
        init();
    }
    
    // If all processes are done
    if (next_arrival_idx >= processes.size() && 
        std::all_of(priority_queues.begin(), priority_queues.end(),
                   [](const auto& pair) { return pair.second.empty(); }) && 
        !current_process) {
        return true; // Simulation complete
    }
    
    // Advance time if no process is ready
    if (!current_process && 
        std::all_of(priority_queues.begin(), priority_queues.end(),
                   [](const auto& pair) { return pair.second.empty(); }) && 
        next_arrival_idx < processes.size()) {
        current_time = processes[next_arrival_idx].getArrivalTime();
    }
    
    // Add any arriving processes
    while (next_arrival_idx < processes.size() && 
           processes[next_arrival_idx].getArrivalTime() <= current_time) {
        int prio = processes[next_arrival_idx].getPriority();
        priority_queues[prio].push(&processes[next_arrival_idx]);
        next_arrival_idx++;
    }
    
    // Get next process if needed
    if (!current_process) {
        current_priority = findHighestPriorityQueue();
        if (current_priority != -1) {
            current_process = priority_queues[current_priority].front();
            priority_queues[current_priority].pop();
            quantum_used = 0;
        }
    }
    
    // Process the current job
    if (current_process) {
        current_process->step(1);
        current_time++;
        quantum_used++;
        
        // Check if time quantum exhausted or process complete
        if (current_process->isDone() || quantum_used >= time_quantum) {
            if (current_process->isDone()) {
                // Process complete
                current_process->setCompletionTime(current_time);
                current_process->setTurnaroundTime(current_process->getCompletionTime() - 
                                                  current_process->getArrivalTime());
                current_process->setWaitingTime(current_process->getTurnaroundTime() - 
                                               current_process->getBurstTime());
            } else {
                // Time quantum expired, put back in queue
                // Check if any higher priority processes arrived
                int new_highest_priority = findHighestPriorityQueue();
                
                if (new_highest_priority != -1 && new_highest_priority < current_priority) {
                    // Higher priority processes available, preempt
                    priority_queues[current_priority].push(current_process);
                    current_priority = new_highest_priority;
                } else {
                    // No higher priority, add back to same queue
                    priority_queues[current_priority].push(current_process);
                }
            }
            
            // Get next process
            current_priority = findHighestPriorityQueue();
            if (current_priority != -1) {
                current_process = priority_queues[current_priority].front();
                priority_queues[current_priority].pop();
                quantum_used = 0;
            } else {
                current_process = nullptr;
            }
        }
    }
    
    return false; // Simulation not complete yet
}

void PriorityRR::print_gantt_chart() {
    std::cout << "Priority Round Robin Gantt Chart (Time Quantum = " << time_quantum << "):\n";
    for (const auto& entry : timeline) {
        std::cout << "[P" << std::get<0>(entry) << "] "
                  << std::get<1>(entry) << "-" << std::get<2>(entry) << " | ";
    }
    std::cout << "\n";
}
