#include "Scheduler.h"
#include <algorithm>

using namespace std;

class FCFS : public Scheduler {
    public:
        void simulate(vector<Process>& processes) override {
            // Sort processes by arrival time 
            sort(processes.begin(), processes.end(),
            [](const Process& a, const Process& b) {
                return a.arrival_time < b.arrival_time;
            });

            int current_time = 0;
        for (auto& p : processes) {
            // Handle CPU idle time
            if (current_time < p.arrival_time) {
                current_time = p.arrival_time;
            }

            // Calculate metrics
            p.waiting_time = current_time - p.arrival_time;
            updateTimeline(p.id, current_time, current_time + p.burst_time);
            
            current_time += p.burst_time;
            p.completion_time = current_time;
            p.turnaround_time = p.completion_time - p.arrival_time;
        }
        }
};