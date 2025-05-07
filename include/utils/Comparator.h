#pragma once

class Comparator
{
public:
    static void runComparativeAnalysis();
    static void configureComparativeAnalysis(int &numProcesses, int &maxArrival, int &minBurst,
                                             int &maxBurst, int &maxPriority, int &quantum);
};