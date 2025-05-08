#include "utils/Comparator.h"
#include "utils/Drawer.h"
#include "core/Scheduler.h"
#include "utils/InputHandler.h"
#include "core/FCFS.h"
#include "core/SJF.h"
#include "core/Priority.h"
#include "core/RR.h"
#include "core/PriorityRR.h"
#include "utils/Selector.h"
#include "core/Process.h"
#include <vector>

#include <iostream>
#include <memory>

void Comparator::runComparativeAnalysis()
{

    std::vector<Process> processes = Selector::selectInputMethod();
    int quantum;

    std::cout << "Enter time quantum (1-100): ";
    std::cin >> quantum;
    while (quantum < 1 || quantum > 100)
    {
        std::cout << "Invalid quantum. Please enter a value between 1 and 100: ";
        std::cin >> quantum;
    }
    std::cout << "\nRunning comparative analysis...\n";
    std::cout << "===================================\n";

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
        std::cout << "Running " << scheduler->getName() << "...\n";
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
    std::cout << "===================================\n";
    std::cout << "Comparative analysis completed.\n";

    // Display comparative results
    Drawer::displayComparativeResults(results, processes.size());
}