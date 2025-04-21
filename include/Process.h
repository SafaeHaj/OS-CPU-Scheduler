#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int id;                 // Process ID
    int arrival_time;       // Time when process arrives
    int burst_time;         // Total CPU time required
    int priority;           // Priority level (lower = higher priority)
    int remaining_time;     // Remaining execution time (for preemptive algorithms)
    int waiting_time;       // Total time spent waiting
    int turnaround_time;    // Completion time - arrival time
    int completion_time;    // Time when process finishes

    // Constructor for easy initialization
    Process(int id, int at, int bt, int prio)
        : id(id), arrival_time(at), burst_time(bt), priority(prio),
          remaining_time(bt), waiting_time(0), turnaround_time(0), completion_time(0) {}
};

#endif // PROCESS_H