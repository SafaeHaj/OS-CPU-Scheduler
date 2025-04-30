#include "Scheduler.h"
#include "Process.h"
#include <queue>
#include <vector>

class Priority: public Scheduler {
    protected:
    struct ComparePriority {
        bool operator()(const Process& p1, const Process& p2) const {
            return p1.priority > p2.priority; 
        }
    };

    std::priority_queue<Process, std::vector<Process>, ComparePriority> process_queue;

    void schedule() override {
        for (const auto& process : this->processes) {
            process_queue.push(process);
        }

        while (!process_queue.empty()) {
            Process current_process = process_queue.top();
            current_process.execute();
            process_queue.pop(); 
            this->calculate_metrics();
        }
    }
};