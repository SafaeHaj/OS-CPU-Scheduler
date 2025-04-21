#ifndef METRICS_H
#define METRICS_H

#include <vector>
#include "Process.h"

class Metrics {
public:
    static void printGanttChart(const std::vector<std::tuple<int, int, int>>& timeline);
    static void calculateMetrics(const std::vector<Process>& processes);
};

#endif // METRICS_H