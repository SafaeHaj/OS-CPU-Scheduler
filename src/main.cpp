#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include "InputHandler.h"
#include "Scheduler.h"
#include "Process.h"
#include "FCFS.h"
#include "SJF.h"
#include "Priority.h"
#include "RR.h"
#include "PriorityRR.h"

// Forward declarations
void displayMainMenu();
std::unique_ptr<Scheduler> selectScheduler();
void printMetrics(const Metrics& metrics);

int main() {
    try {
        std::vector<Process> processes;
        int inputChoice;

        // Display main menu
        displayMainMenu();
        std::cin >> inputChoice;

        // Handle input method
        if (inputChoice == 1) {
            std::string filename;
            std::cout << "Enter input file path: ";
            std::cin >> filename;
            processes = InputHandler::readFromFile(filename);
        } else if (inputChoice == 2) {
            int count, max_arrival, min_burst, max_burst, max_priority;
            std::cout << "Number of processes: ";
            std::cin >> count;
            std::cout << "Max arrival time: ";
            std::cin >> max_arrival;
            std::cout << "Min burst time: ";
            std::cin >> min_burst;
            std::cout << "Max burst time: ";
            std::cin >> max_burst;
            std::cout << "Max priority: ";
            std::cin >> max_priority;
            
            processes = InputHandler::generateRandomProcesses(
                count, max_arrival, min_burst, max_burst, max_priority);
        } else {
            throw std::invalid_argument("Invalid choice");
        }

        // Select scheduler
        auto scheduler = selectScheduler();
        scheduler->processes = processes;
        scheduler->run_simulation();

        // Display results
        scheduler->print_gantt_chart();
        printMetrics(scheduler->metrics);

    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

void displayMainMenu() {
    std::cout << "=== CPU Scheduler Simulator ===\n"
              << "1. Read processes from file\n"
              << "2. Generate random processes\n"
              << "Enter your choice: ";
}

std::unique_ptr<Scheduler> selectScheduler() {
    int choice;
    std::cout << "\n=== Scheduling Algorithms ===\n"
              << "1. FCFS (First-Come First-Served)\n"
              << "2. SJF (Shortest Job First)\n"
              << "3. Priority Scheduling\n"
              << "4. Round Robin (RR)\n"
              << "5. Priority with Round Robin\n"
              << "Enter your choice: ";
    std::cin >> choice;

    switch(choice) {
        case 1: return std::make_unique<FCFS>();
        case 2: return std::make_unique<SJF>();
        case 3: return std::make_unique<Priority>();
        case 4: {
            int quantum;
            std::cout << "Enter time quantum: ";
            std::cin >> quantum;
            return std::make_unique<RR>(quantum);
        }
        case 5: {
            int quantum;
            std::cout << "Enter time quantum: ";
            std::cin >> quantum;
            return std::make_unique<PriorityRR>(quantum);
        }
        default: throw std::invalid_argument("Invalid scheduler choice");
    }
}



void printMetrics(const Metrics& metrics) {
    std::cout << "\n=== Performance Metrics ===\n"
              << "Average Waiting Time: " << metrics.avg_waiting_time << "\n"
              << "Average Turnaround Time: " << metrics.avg_turnaround_time << "\n"
              << "CPU Utilization: " << metrics.cpu_utilization << "%\n"
              << "Total Idle Time: " << metrics.total_idle_time << "\n";
}