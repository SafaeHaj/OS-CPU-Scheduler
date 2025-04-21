#include <vector>
#include <unordered_map>

class Scheduler {
    protected:
        std::vector<Process> processes;  
        Process* current_process = nullptr;
        int current_time = 0;
        Metrics metrics;

    public:
        virtual void schedule() = 0; // virtual method that will be overridden in derived classes
        void run_simulation();        
        void calculate_metrics(); // to define later on     
    };


    struct Metrics {
        struct ProcessStats {
            int waiting_time;
            int turnaround_time;
        };
    
        float avg_waiting_time;
        float avg_turnaround_time;
        float cpu_utilization;
        int total_idle_time;
    
        std::unordered_map<int, ProcessStats> process_details;
    
        void reset() {
            avg_waiting_time = 0.0f;
            avg_turnaround_time = 0.0f;
            cpu_utilization = 0.0f;
            total_idle_time = 0;
            process_details.clear();
        }
    };