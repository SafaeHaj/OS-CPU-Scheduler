#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "core/Scheduler.h"
#include "core/FCFS.h"
#include "core/SJF.h"
#include "core/Priority.h"
#include "core/RR.h"
#include "core/PriorityRR.h"
#include "InputHandler.h"

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
void drawProgressBar(const Process& process, int width, int line);
std::unique_ptr<Scheduler> selectSchedulingAlgorithm();
std::vector<Process> generateRandomProcesses();

int main() {
    // Get scheduler 
    auto scheduler = selectSchedulingAlgorithm();
    
    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Generate random processes with user-configurable parameters
    scheduler->processes = generateRandomProcesses();
    
    // Brief pause to let user see the generated processes
    std::cout << "\nProcess set generated. Starting visualization in 2 seconds...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Clear screen and hide cursor
    std::cout << "\033[2J\033[?25l";
    
    // Print header
    std::cout << "Running " << scheduler->getName() << " simulation...\n\n";
    
    // Print process details in a table format
    std::cout << "PROCESS SET:\n";
    std::cout << "ID | Arrival | Burst | Priority\n";
    std::cout << "----------------------------\n";
    for (const auto& p : scheduler->processes) {
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
    
    // Clear screen again before starting animation
    std::cout << "\033[2J";
    
    std::cout << "Running " << scheduler->getName() << " simulation...\n";
    std::cout << "Time: 0\n\n";
    
    while (!done) {
        // Show current time
        std::cout << "\033[2;0H";
        std::cout << "Time: " << current_time << "    ";
        
        // Update all progress bars
        for (size_t j = 0; j < scheduler->processes.size(); ++j) {
            drawProgressBar(scheduler->processes[j], width, j + 4);
        }
        
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
    
    return 0;
}

// Draw a progress bar at specific line position
void drawProgressBar(const Process& process, int width = 50, int line = 0) {
    float fraction = float(process.current_progress) / float(process.burst_time);
    int filled = int(fraction * width);
    std::string color = COLORS[process.id % 6];
    
    // Move cursor to specific line
    std::cout << "\033[" << line << ";0H";
    
    // Draw the bar with color
    std::cout << color << "Process " << process.name << " [";
    for (int i = 0; i < filled; ++i) std::cout << "█";
    for (int i = filled; i < width; ++i) std::cout << " ";
    std::cout << "] " << int(fraction * 100) << "%";
    
    // If process is done, show metrics
    if (process.isDone()) {
        std::cout << " | Turnaround: " << process.getTurnaroundTime()
                  << ", Waiting: " << process.getWaitingTime();
    }
    
    std::cout << RESET;
    std::cout.flush();
}

// Show menu and get user choice
std::unique_ptr<Scheduler> selectSchedulingAlgorithm() {
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
    while (choice < 1 || choice > 5) {
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;
    }
    
    int quantum = 5;
    if (choice == 4 || choice == 5) {
        std::cout << "Enter time quantum: ";
        std::cin >> quantum;
    }
    
    switch (choice) {
        case 1: return std::make_unique<FCFS>();
        case 2: return std::make_unique<SJF>();
        case 3: return std::make_unique<Priority>();
        case 4: return std::make_unique<RR>(quantum);
        case 5: return std::make_unique<PriorityRR>(quantum);
        default: return std::make_unique<FCFS>();
    }
}

// Generate random processes with reasonable defaults
std::vector<Process> generateRandomProcesses() {
    std::cout << "\nRandom Process Generation\n";
    std::cout << "-------------------------\n";
    
    int count = 5; // Default values that produce good visualization
    int max_arrival = 10;
    int min_burst = 3;
    int max_burst = 20;
    int max_priority = 10;
    
    std::cout << "Enter process count [default=5]: ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) count = std::stoi(input);
    
    std::cout << "Enter max arrival time [default=10]: ";
    std::getline(std::cin, input);
    if (!input.empty()) max_arrival = std::stoi(input);
    
    std::cout << "Enter min burst time [default=3]: ";
    std::getline(std::cin, input);
    if (!input.empty()) min_burst = std::stoi(input);
    
    std::cout << "Enter max burst time [default=20]: ";
    std::getline(std::cin, input);
    if (!input.empty()) max_burst = std::stoi(input);
    
    std::cout << "Enter max priority [default=10]: ";
    std::getline(std::cin, input);
    if (!input.empty()) max_priority = std::stoi(input);
    
    return InputHandler::generateRandomProcesses(
        count, max_arrival, min_burst, max_burst, max_priority);
}