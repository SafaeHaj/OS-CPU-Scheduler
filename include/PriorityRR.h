#pragma once
#include "Scheduler.h"

class PriorityRR : public Scheduler {
private:
    int time_quantum;
public:
    PriorityRR(int quantum) : time_quantum(quantum) {}
    void schedule() override;
    void print_gantt_chart() override;
};