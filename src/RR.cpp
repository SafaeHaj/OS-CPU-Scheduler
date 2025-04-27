#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include "Process.h"
#include "Scheduler.h"





// Round Robin Scheduler
class RRScheduler : public Scheduler {
    int quantum;
public:
    RRScheduler(int q) : quantum(q) {}

    void schedule() override {
        std::sort(processes.begin(), processes.end(),
            [](const Process& a, const Process& b) {
                return a.getArrivalTime() < b.getArrivalTime();
            });

        current_time = 0;
        std::queue<Process*> ready_queue;
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

            Process* p = ready_queue.front();
            ready_queue.pop();

            int time_exec = std::min(quantum, p->getRemainingTime());
            p->setRemainingTime(p->getRemainingTime() - time_exec);
            current_time += time_exec;

            while (next < processes.size() && 
                   processes[next].getArrivalTime() <= current_time) {
                ready_queue.push(&processes[next]);
                next++;
            }

            if (p->getRemainingTime() > 0) {
                ready_queue.push(p);
            } else {
                p->setCompletionTime(current_time);
                p->updateWaitingTime(p->getTurnaroundTime() - p->getBurstTime());
                
                Metrics::ProcessStats stats;
                stats.waiting_time = p->getWaitingTime();
                stats.turnaround_time = p->getTurnaroundTime();
                metrics.process_details[p->getId()] = stats;
            }
        }
        calculate_metrics();
    }
};