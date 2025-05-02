#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
public:
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int current_progress;  
    std::string name;     
     
    Process(int id, int arrival_time, int burst_time, int priority)
        : id(id), arrival_time(arrival_time), burst_time(burst_time), priority(priority),
          remaining_time(burst_time), waiting_time(0), turnaround_time(0),
          completion_time(0), current_progress(0) {
        name = "P" + std::to_string(id);
    }
    
    bool isDone() const { return remaining_time <= 0; }
    void step(int amount = 1) { 
        current_progress += amount; 
        remaining_time = burst_time - current_progress;
    }
    
    int getTurnaroundTime() const { return completion_time - arrival_time; }
    int getWaitingTime() const { return getTurnaroundTime() - burst_time; }
    int getArrivalTime() const { return arrival_time; }
    int getBurstTime() const { return burst_time; }
    int getPriority() const { return priority; }
    int getId() const { return id; }
    int getRemainingTime() const { return remaining_time; }
    int getCompletionTime() const { return completion_time; }
    
    void setRemainingTime(int time) { remaining_time = time; }
    void setCompletionTime(int time) { completion_time = time; }
    void setTurnaroundTime(int time) { turnaround_time = time; }
    void setWaitingTime(int time) { waiting_time = time; }
};

#endif // PROCESS_H