#include <vector>
#include <unordered_map>
#include "Process.h"

class Scheduler {
    struct Metrics {
        struct ProcessStats {
            int waiting_time;
            int turnaround_time;
        };
    
        float avg_waiting_time;
        float avg_turnaround_time;
        float cpu_utilization;
        int total_idle_time;
    
        std::unordered_map<int, ProcessStats> process_details; // map each process ID to its stats
    
        void reset() {
            avg_waiting_time = 0.0f;
            avg_turnaround_time = 0.0f;
            cpu_utilization = 0.0f;
            total_idle_time = 0;
            process_details.clear();
        }
    };

    protected:
        std::vector<Process> processes;  
        Process* current_process = nullptr;
        int current_time = 0;
        Metrics metrics;

    public:
        virtual void schedule() = 0; // virtual method that will be overridden in derived classes
        void calculate_metrics(); // to define later on     
};