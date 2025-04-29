#pragma once
#include "Scheduler.h"

class RR : public Scheduler {
private:
    int time_quantum;
public:
    RR(int quantum) : time_quantum(quantum) {}
    void schedule() override;
    void print_gantt_chart() override;
};