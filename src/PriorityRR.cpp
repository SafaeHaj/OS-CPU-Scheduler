#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include "Process.h"
#include "Scheduler.h"





// Priority with Round Robin (per priority level)
class PriorityRRScheduler : public Scheduler {
    int quantum;
    std::map<int, std::queue<Process*>> queues; // Lower key = higher priority

public:
    PriorityRRScheduler(int q) : quantum(q) {}

    void schedule() override {
        std::sort(processes.begin(), processes.end(),
            [](const Process& a, const Process& b) {
                return a.getArrivalTime() < b.getArrivalTime();
            });

        current_time = 0;
        size_t next = 0;
        Process* current_process = nullptr;
        int remaining_quantum = 0;

        while (true) {
            // Add arrived processes
            while (next < processes.size() && 
                   processes[next].getArrivalTime() <= current_time) {
                int prio = processes[next].getPriority();
                queues[prio].push(&processes[next]);
                next++;
            }

            // Check for higher priority processes
            if (current_process) {
                auto it = queues.begin();
                while (it != queues.end() && it->first >= current_process->getPriority()) {
                    ++it;
                }
                if (it != queues.end() && !it->second.empty()) {
                    queues[current_process->getPriority()].push(current_process);
                    current_process = nullptr;
                }
            }

            // Find highest priority queue
            auto it = queues.begin();
            while (it != queues.end() && it->second.empty()) ++it;

            if (it == queues.end()) {
                if (next >= processes.size()) break;
                current_time = processes[next].getArrivalTime();
                continue;
            }

            Process* p = it->second.front();
            it->second.pop();

            int exec_time = std::min(quantum, p->getRemainingTime());
            p->setRemainingTime(p->getRemainingTime() - exec_time);
            current_time += exec_time;

            if (p->getRemainingTime() > 0) {
                queues[p->getPriority()].push(p);
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