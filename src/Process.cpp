#include "Process.h"

Process::Process(int id, int at, int bt, int prio)
    : id(id), arrival_time(at), burst_time(bt),
      priority(prio), remaining_time(bt),
      waiting_time(0), turnaround_time(0), completion_time(0) {}

// Getter implementations
int Process::getId() const { return id; }
int Process::getArrivalTime() const { return arrival_time; }
int Process::getBurstTime() const { return burst_time; }
int Process::getPriority() const { return priority; }
int Process::getRemainingTime() const { return remaining_time; }
int Process::getWaitingTime() const { return waiting_time; }
int Process::getTurnaroundTime() const { return turnaround_time; }
int Process::getCompletionTime() const { return completion_time; }

// Setter implementations
void Process::setRemainingTime(int rt) { remaining_time = rt; }
void Process::updateWaitingTime(int wt) { waiting_time += wt; }
void Process::setCompletionTime(int ct) {
    completion_time = ct;
    turnaround_time = completion_time - arrival_time;
}
void Process::setTurnaroundTime(int tt) { turnaround_time = tt; }
void Process::setWaitingTime(int wt) { waiting_time = wt; } 