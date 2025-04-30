#pragma once
#include "Scheduler.h"


class Priority : public Scheduler {
    public:
        void schedule() override;
        void print_gantt_chart() override;
};