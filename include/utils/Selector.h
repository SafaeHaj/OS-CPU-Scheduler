#pragma once

#include "core/Scheduler.h"
#include <memory>
#include <vector>

class Selector
{
public:
    static int selectOperationMode();
    static std::unique_ptr<Scheduler> selectSchedulingAlgorithm();
    static std::vector<Process> selectInputMethod();
};