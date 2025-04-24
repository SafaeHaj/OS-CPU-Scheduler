#include "Scheduler.h"
#include "Process.h"
#include <queue>

class RR: public Scheduler {
    private:
    int quantum;
    std::queue<Process> process_queue;

    public:
    RR(int quantum) : quantum(quantum) {}
    // code still in progress, might have to further modify Process class to better implement the cut program behavior
    /*
    void schedule() override {
        for (const auto& process : this->processes) {
            process_queue.push(process);
        }

        while (!process_queue.empty()) {
            Process current_process = process_queue.front();
            int start_time = time.now();

            while (time.now() - start_time < quantum && current_process.remaining_time > 0) { // this doesnt actually work
                current_process.execute();
                if (time.now() - start_time >= quantum) {
                    break;
                }
            }

            process_queue.pop();

            if (current_process.remaining_time > quantum) {
                current_process.remaining_time -= quantum;
                current_time += quantum;
                process_queue.push(current_process);
            } else {
                current_time += current_process.remaining_time;
                current_process.remaining_time = 0;
                current_process.is_completed = true;
                this->calculate_metrics();
            }

        }
    }
    */
};