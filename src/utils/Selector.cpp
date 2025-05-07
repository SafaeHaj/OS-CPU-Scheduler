#include "utils/Selector.h"
#include <iostream>
#include <limits>
#include "core/FCFS.h"
#include "core/SJF.h"
#include "core/Priority.h"
#include "core/RR.h"
#include "core/PriorityRR.h"
#include "utils/InputHandler.h"
#include <algorithm>

std::unique_ptr<Scheduler> Selector::selectSchedulingAlgorithm()
{
    std::cout << "===================================\n";
    std::cout << "   CPU SCHEDULER VISUALIZER\n";
    std::cout << "===================================\n\n";
    std::cout << "Select Scheduling Algorithm:\n";
    std::cout << "1. First Come First Served (FCFS)\n";
    std::cout << "2. Shortest Job First (SJF)\n";
    std::cout << "3. Priority Scheduling\n";
    std::cout << "4. Round Robin\n";
    std::cout << "5. Priority Round Robin\n";

    int choice = 0;
    while (choice < 1 || choice > 5)
    {
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
        }
    }

    float quantum = 5;
    if (choice == 4 || choice == 5)
    {
        while (true)
        {
            std::cout << "Enter time quantum (1-100): ";
            std::cin >> quantum;
            if (quantum >= 1 && quantum <= 100)
                break;
            std::cout << "Invalid quantum. Please enter a value between 1 and 100.\n";
        }
    }

    switch (choice)
    {
    case 1:
        return std::make_unique<FCFS>();
    case 2:
        return std::make_unique<SJF>();
    case 3:
        return std::make_unique<Priority>();
    case 4:
        return std::make_unique<RR>(quantum);
    case 5:
        return std::make_unique<PriorityRR>(quantum);
    default:
        return std::make_unique<FCFS>();
    }
}

std::vector<Process> Selector::selectInputMethod()
{
    std::cout << "\nSelect Input Method:\n";
    std::cout << "1. Read from file\n";
    std::cout << "2. Generate random processes\n";
    std::cout << "3. Enter manually\n";

    int choice = 0;
    while (choice < 1 || choice > 3)
    {
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
        }
    }

    std::cin.ignore(); // Clear newline

    switch (choice)
    {
    case 1:
    {
        std::string filename;
        std::cout << "Enter input file path: ";
        std::getline(std::cin, filename);
        return InputHandler::readFromFile(filename);
    }
    case 2:
    {
        std::cout << "\nRandom Process Generation\n";
        std::cout << "-------------------------\n";

        int count = 5, max_arrival = 10, min_burst = 3, max_burst = 20, max_priority = 10;

        auto getInput = [](const std::string &prompt, int defaultVal)
        {
            std::cout << prompt << " [default=" << defaultVal << "]: ";
            std::string input;
            std::getline(std::cin, input);
            return input.empty() ? defaultVal : std::stoi(input);
        };

        count = getInput("Enter process count", 5);
        max_arrival = getInput("Enter max arrival time", 10);
        min_burst = getInput("Enter min burst time", 3);
        max_burst = getInput("Enter max burst time", 20);
        max_priority = getInput("Enter max priority", 10);

        return InputHandler::generateRandomProcesses(
            count, max_arrival, min_burst, max_burst, max_priority);
    }
    case 3:
    {
        std::vector<Process> processes;
        int id = 0;
        std::cout << "\nManual Process Entry (Enter negative arrival time to finish)\n";

        while (true)
        {
            int arrival, burst, priority;
            std::cout << "\nProcess P" << id << ":\n";

            std::cout << "Arrival time: ";
            std::cin >> arrival;
            if (arrival < 0)
                break;

            std::cout << "Burst time: ";
            std::cin >> burst;
            if (burst <= 0)
            {
                std::cout << "Burst time must be positive!\n";
                continue;
            }

            std::cout << "Priority: ";
            std::cin >> priority;
            if (priority < 0)
            {
                std::cout << "Priority must be non-negative!\n";
                continue;
            }

            processes.emplace_back(id++, arrival, burst, priority);
            std::cin.ignore(); // Clear newline
        }

        // Sort by arrival time
        std::sort(processes.begin(), processes.end(),
                  [](const Process &a, const Process &b)
                  {
                      return a.getArrivalTime() < b.getArrivalTime();
                  });

        return processes;
    }
    default:
        return InputHandler::generateRandomProcesses(5, 10, 3, 20, 10);
    }
}
int Selector::selectOperationMode()
{
    std::cout << "===================================\n";
    std::cout << "   CPU SCHEDULER ANALYSIS TOOL\n";
    std::cout << "===================================\n\n";
    std::cout << "Select Operation Mode:\n";
    std::cout << "1. Single Algorithm Simulation\n";
    std::cout << "2. Comparative Analysis (All Algorithms)\n";

    int choice = 0;
    while (choice < 1 || choice > 2)
    {
        std::cout << "Enter your choice (1-2): ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
        }
    }
    return choice;
}
