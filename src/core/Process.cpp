#include "core/Process.h"

Process::Process(int id, int arrival_time, int burst_time, int priority)
    : id(id), arrival_time(arrival_time), burst_time(burst_time), priority(priority),
      remaining_time(burst_time), waiting_time(0), turnaround_time(0),
      completion_time(0), current_progress(0)
{
    name = "P" + std::to_string(id);
}

bool Process::isDone() const 
{
    return remaining_time <= 0;
}

void Process::step(int amount)
{
    current_progress += amount;
    remaining_time = burst_time - current_progress;
}

int Process::getTurnaroundTime() const 
{
    return completion_time - arrival_time;
}

int Process::getWaitingTime() const 
{
    return getTurnaroundTime() - burst_time;
}

int Process::getArrivalTime() const 
{
    return arrival_time;
}

int Process::getBurstTime() const 
{
    return burst_time;
}

int Process::getPriority() const 
{
    return priority;
}

int Process::getId() const 
{
    return id;
}

int Process::getRemainingTime() const 
{
    return remaining_time;
}

int Process::getCompletionTime() const 
{
    return completion_time;
}

void Process::setRemainingTime(int time) 
{
    remaining_time = time;
}

void Process::setCompletionTime(int time) 
{
    completion_time = time;
}

void Process::setTurnaroundTime(int time) 
{
    turnaround_time = time;
}

void Process::setWaitingTime(int time) 
{
    waiting_time = time;
}
