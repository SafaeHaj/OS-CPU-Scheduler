
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include "Process.h"
#include "Scheduler.h"




// Priority Scheduling (Non-preemptive)
class PriorityScheduler : public Scheduler {
public:
    void schedule() override {
        std::sort(processes.begin(), processes.end(),
            [](const Process& a, const Process& b) {
                return a.getArrivalTime() < b.getArrivalTime();
            });

        current_time = 0;
        std::priority_queue<Process*, std::vector<Process*>, 
            bool(*)(Process*, Process*)> ready_queue(
                [](Process* a, Process* b) {
                    return a->getPriority() > b->getPriority();
                });

        size_t next = 0;
        while (next < processes.size() || !ready_queue.empty()) {
            while (next < processes.size() && 
                   processes[next].getArrivalTime() <= current_time) {
                ready_queue.push(&processes[next]);
                next++;
            }

            if (ready_queue.empty()) {
                current_time = processes[next].getArrivalTime();
                continue;
            }

            Process* p = ready_queue.top();
            ready_queue.pop();

            p->updateWaitingTime(current_time - p->getArrivalTime());
            current_time += p->getBurstTime();
            p->setCompletionTime(current_time);

            Metrics::ProcessStats stats;
            stats.waiting_time = p->getWaitingTime();
            stats.turnaround_time = p->getTurnaroundTime();
            metrics.process_details[p->getId()] = stats;
        }
        calculate_metrics();
    }
};