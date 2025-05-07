#pragma once

#include <vector>
#include "core/Process.h"
#include "core/Scheduler.h"

class Drawer
{
public:
    static void drawProgressBar(const Process &process, int width, int line);
    static void drawFinishedTable(const std::vector<Process> &finished, int startLine, int startCol);
    static void drawFinalMetrics(const Scheduler &scheduler, int startLine);
    static void displayComparativeResults(const std::vector<std::pair<std::string, Metrics>> &results, int processCount);
};