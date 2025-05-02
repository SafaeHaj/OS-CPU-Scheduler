#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <limits>

#include "core/Scheduler.h"
#include "core/FCFS.h"
#include "core/SJF.h"
#include "core/Priority.h"
#include "core/RR.h"
#include "core/PriorityRR.h"
#include "InputHandler.h"
#include <iomanip>

// ANSI color codes
const std::string RESET = "\033[0m";
const std::string COLORS[] = {
    "\033[1;31m", // Red
    "\033[1;32m", // Green
    "\033[1;33m", // Yellow
    "\033[1;34m", // Blue
    "\033[1;35m", // Magenta
    "\033[1;36m"  // Cyan
};

// Forward declarations
void drawProgressBar(const Process &process, int width, int line);
void drawFinishedTable(const std::vector<Process> &finished, int startLine, int startCol);
std::unique_ptr<Scheduler> selectSchedulingAlgorithm();
std::vector<Process> selectInputMethod();

int main()
{
    try
    {
        // Get scheduler
        auto scheduler = selectSchedulingAlgorithm();

        // Get processes based on input method
        scheduler->processes = selectInputMethod();

        // Brief pause to let user see the generated processes
        std::cout << "\nStarting visualization in 2 seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Clear screen and hide cursor
        std::cout << "\033[2J\033[?25l";

        // Print header
        std::cout << "Running " << scheduler->getName() << " simulation...\n\n";

        // Print process details in a table format
        std::cout << "PROCESS SET:\n";
        std::cout << "ID | Arrival | Burst | Priority\n";
        std::cout << "----------------------------\n";
        for (const auto &p : scheduler->processes)
        {
            std::cout << "P" << p.id << " | "
                      << p.arrival_time << " | "
                      << p.burst_time << " | "
                      << p.priority << "\n";
        }
        std::cout << "\n\n";

        // Small delay to let user see process set
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Initialize scheduler
        scheduler->init();

        // Run simulation step by step
        bool done = false;
        const int width = 50;
        const int delay_ms = 30;
        int current_time = 0;
        std::vector<Process> finished_processes;

        // Clear screen again before starting animation
        std::cout << "\033[2J";

        std::cout << "Running " << scheduler->getName() << " simulation...\n";
        std::cout << "Time: 0\n\n";

        while (!done)
        {
            // Show current time
            std::cout << "\033[2;0H";
            std::cout << "Time: " << current_time << "    ";

            // Update all progress bars
            for (size_t j = 0; j < scheduler->processes.size(); ++j)
            {
                drawProgressBar(scheduler->processes[j], width, j + 4);
            }

            // Track finished processes
            for (auto &p : scheduler->processes)
            {
                if (p.isDone() && std::find(finished_processes.begin(), finished_processes.end(), p) == finished_processes.end())
                {
                    finished_processes.push_back(p);
                }
            }

            // Draw finished processes table
            drawFinishedTable(finished_processes, 4, 70);

            // Take one step in simulation
            done = scheduler->step();
            current_time++;

            // Wait a bit
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        }

        // Calculate metrics
        scheduler->calculate_metrics();

        // Move cursor below all progress bars and show it again
        std::cout << "\033[" << scheduler->processes.size() + 5 << ";0H";
        std::cout << "Simulation complete!\n";
        std::cout << "Average turnaround time: " << scheduler->metrics.avg_turnaround_time << "\n";
        std::cout << "Average waiting time: " << scheduler->metrics.avg_waiting_time << "\n";
        std::cout << "CPU Utilization: " << scheduler->metrics.cpu_utilization << "%\n";
        std::cout << "\033[?25h";
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nError: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

void drawProgressBar(const Process &process, int width, int line)
{
    float fraction = float(process.current_progress) / float(process.burst_time);
    int filled = int(fraction * width);
    std::string color = COLORS[process.id % 6];

    // Move cursor to specific line
    std::cout << "\033[" << line << ";0H";

    // Draw the bar with color
    std::cout << color << "Process " << process.name << " [";
    for (int i = 0; i < filled; ++i)
        std::cout << "█";
    for (int i = filled; i < width; ++i)
        std::cout << " ";
    std::cout << "] " << int(fraction * 100) << "%" << RESET;
    std::cout.flush();
}

void drawFinishedTable(const std::vector<Process> &finished, int startLine, int startCol)
{
    std::cout << "\033[" << startLine << ";" << startCol << "H";
    std::cout << "┌───────────────┬───────────────┬──────────────┐\n";
    std::cout << "\033[" << startLine + 1 << ";" << startCol << "H";
    std::cout << "│ Finished Proc │ Turnaround    │ Waiting Time │\n";
    std::cout << "\033[" << startLine + 2 << ";" << startCol << "H";
    std::cout << "├───────────────┼───────────────┼──────────────┤";

    for (size_t i = 0; i < finished.size(); ++i)
    {
        std::cout << "\033[" << startLine + 3 + i << ";" << startCol << "H";
        std::cout << "│ P" << std::left << std::setw(12) << finished[i].id
                  << "│ " << std::setw(13) << finished[i].getTurnaroundTime()
                  << "│ " << std::setw(12) << finished[i].getWaitingTime() << " │";
    }

    if (!finished.empty())
    {
        std::cout << "\033[" << startLine + 3 + finished.size() << ";" << startCol << "H";
        std::cout << "└───────────────┴───────────────┴──────────────┘";
    }
    std::cout.flush();
}

std::unique_ptr<Scheduler> selectSchedulingAlgorithm()
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

    int quantum = 5;
    if (choice == 4 || choice == 5)
    {
        while (true)
        {
            std::cout << "Enter time quantum (1-100): ";
            std::cin >> quantum;
            if (quantum > 0 && quantum <= 100)
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

std::vector<Process> selectInputMethod()
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