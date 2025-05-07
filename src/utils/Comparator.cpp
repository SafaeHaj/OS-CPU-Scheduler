#include "utils/Comparator.h"
#include "utils/Drawer.h"
#include "core/Scheduler.h"
#include "utils/InputHandler.h"
#include "core/FCFS.h"
#include "core/SJF.h"
#include "core/Priority.h"
#include "core/RR.h"
#include "core/PriorityRR.h"

#include <iostream>
#include <memory>

void Comparator::runComparativeAnalysis()
{

    int numProcesses, maxArrival, minBurst, maxBurst, maxPriority, quantum;
    configureComparativeAnalysis(numProcesses, maxArrival, minBurst, maxBurst, maxPriority, quantum);

    // Generate random processes
    auto processes = InputHandler::generateRandomProcesses(
        numProcesses, maxArrival, minBurst, maxBurst, maxPriority);

    std::vector<std::pair<std::string, Metrics>> results;
    std::vector<std::unique_ptr<Scheduler>> schedulers;

    // Create all schedulers
    schedulers.push_back(std::make_unique<FCFS>());
    schedulers.push_back(std::make_unique<SJF>());
    schedulers.push_back(std::make_unique<Priority>());
    schedulers.push_back(std::make_unique<RR>(quantum));
    schedulers.push_back(std::make_unique<PriorityRR>(quantum));

    // Run each scheduler
    for (auto &scheduler : schedulers)
    {
        // Copy processes for each scheduler
        scheduler->processes = processes;

        // Fast simulation without visualization
        scheduler->init();
        bool done = false;
        while (!done)
        {
            done = scheduler->step();
        }
        scheduler->calculate_metrics();

        // Store results
        results.emplace_back(scheduler->getName(), scheduler->metrics);
    }

    // Display comparative results
    Drawer::displayComparativeResults(results, numProcesses);
}

void Comparator::configureComparativeAnalysis(int &numProcesses, int &maxArrival, int &minBurst,
                                              int &maxBurst, int &maxPriority, int &quantum)
{
    std::cout << "\n\033[1;36m=== Comparative Analysis Configuration ===\033[0m\n";
    std::cout << "Press Enter to use default values\n\n";

    std::cout << " Take in account that one u (time unit) here is 1ms\n\n";

    std::cout << "Number of processes [default=100]: ";
    std::cin >> numProcesses;
    if (std::cin.fail() || numProcesses < 1)
        numProcesses = 100;

    std::cout << "Maximum arrival time [default=100u]: ";
    std::cin >> maxArrival;
    if (std::cin.fail() || maxArrival < 0)
        maxArrival = 100;

    do
    {
        std::cout << "Minimum burst time [default=3u]: ";
        std::cin >> minBurst;
        if (std::cin.fail() || minBurst < 1)
            minBurst = 3;

        std::cout << "Maximum burst time [default=20u]: ";
        std::cin >> maxBurst;
        if (std::cin.fail() || maxBurst <= minBurst)
            maxBurst = 20;

        if (maxBurst <= minBurst)
        {
            std::cerr << "Max burst must be > min burst (" << minBurst << ")\n";
        }
    } while (maxBurst <= minBurst);

    std::cout << "Maximum priority [default=10]: ";
    std::cin >> maxPriority;
    if (std::cin.fail() || maxPriority < 1)
        maxPriority = 10;

    std::cout << "RR time quantum [default=5u]: ";
    std::cin >> quantum;
    if (std::cin.fail() || quantum < 1)
        quantum = 5;
}