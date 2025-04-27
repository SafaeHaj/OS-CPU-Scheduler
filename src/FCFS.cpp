#include "Scheduler.h"
#include <vector>
#include <algorithm> // for std::sort



class FCFS : public Scheduler {
    public: 
    void schedule() override {
        // Let's sort the processes vector by arrival time
        std :: sort(processes.begin(), processes.end(),
    [](const Process& a , const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });
    current_time = 0;
    for (auto& p : processes){

        // Handle the CPU idle time
        if (current_time < p.getArrivalTime()){
            metrics.total_idl_time += p.getArrivalTime() - current_time;
            current_time = p.getArrivalTime();
        }
        p.updateWaitingTime(current_time - p.getArrivalTime());
        current_time += p.getBurstTime();
        p.setCompletionTime(current_time);

        Metrics:: ProcessStats stats;

        stats.waiting_time = p.getWaitingTime();
        stats.turnaround_time = p.getTurnaroundTime();
        metrics.process_details[p.getId()] = stats;
    }
    calculate_metrics();
    }
};