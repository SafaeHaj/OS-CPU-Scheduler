#include "core/FCFS.h"
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

bool FCFS::init() {
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), 
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });
    
    current_time = 0;
    current_process_idx = 0;
    simulation_started = true;
    
    // Set current process if one is available at time 0
    if (!processes.empty() && processes[0].getArrivalTime() <= current_time) {
        current_process = &processes[current_process_idx];
    }
    
    return true;
}

bool FCFS::step() {
    if (!simulation_started) {
        init();
    }
    
    if (current_process_idx >= processes.size()) {
        return true; // Simulation complete
    }
    
    // If no current process or waiting for arrival
    if (!current_process) {
        if (current_process_idx < processes.size()) {
            // Move time forward to next process arrival
            current_time = processes[current_process_idx].getArrivalTime();
            current_process = &processes[current_process_idx];
        }
    }
    
    // Process the current job
    if (current_process) {
        current_process->step(1);
        current_time++;
        
        // If process complete, move to next one
        if (current_process->isDone()) {
            current_process->setCompletionTime(current_time);
            current_process->setTurnaroundTime(current_process->getCompletionTime() - current_process->getArrivalTime());
            current_process->setWaitingTime(current_process->getTurnaroundTime() - current_process->getBurstTime());
            
            current_process_idx++;
            if (current_process_idx < processes.size()) {
                // Set next process if available
                if (processes[current_process_idx].getArrivalTime() <= current_time) {
                    current_process = &processes[current_process_idx];
                } else {
                    current_process = nullptr; // Will wait for next arrival
                }
            } else {
                current_process = nullptr;
                return true; // Simulation complete
            }
        }
    }
    
    return false; // Simulation not complete yet
}

void FCFS::print_gantt_chart() {
    std::cout << "FCFS Gantt Chart:\n";
    for (const auto& entry : timeline) {
        std::cout << "[P" << std::get<0>(entry) << "] "
                  << std::get<1>(entry) << "-" << std::get<2>(entry) << " | ";
    }
    std::cout << "\n";
}