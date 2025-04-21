#include <iostream>
#include <memory>
#include "InputHandler.h"
#include "Scheduler.h"
#include "Metrics.h"

// Forward declarations
void showMenu();
std::unique_ptr<Scheduler> selectScheduler();

int main() {
    std::vector<Process> processes;
    int choice;

    // Input selection
    std::cout << "Choose input method:\n"
              << "1. Read from file\n"
              << "2. Generate random processes\n";
    std::cin >> choice;

    if (choice == 1) {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;
        processes = InputHandler::readFromFile(filename);
    } else {
        int count, max_arrival, min_burst, max_burst, max_priority;
        std::cout << "Number of processes: ";
        std::cin >> count;
        // ... get other parameters ...
        processes = InputHandler::generateRandomProcesses(
            count, max_arrival, min_burst, max_burst, max_priority);
    }

    auto scheduler = selectScheduler();
    scheduler->simulate(processes);

    Metrics::printGanttChart(scheduler->timeline);
    Metrics::calculateMetrics(processes);

    return 0;
}

// Implement menu functions similarly...