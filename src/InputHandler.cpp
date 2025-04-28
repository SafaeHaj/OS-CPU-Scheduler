#include "InputHandler.h"
#include <fstream>
#include <sstream>
#include <random>
#include <stdexcept>
#include <algorithm>

std::vector<Process> InputHandler::readFromFile(const std::string& filename) {
    std::vector<Process> processes;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file " + filename);
    }

    std::string line;
    int line_num = 0;
    while (std::getline(file, line)) {
        line_num++;
        std::istringstream iss(line);
        int id, arrival, burst, priority;
        
        if (!(iss >> id >> arrival >> burst >> priority)) {
            throw std::runtime_error("Invalid format in line " + std::to_string(line_num));
        }

        // Validate input values
        if (arrival < 0) {
            throw std::runtime_error("Negative arrival time in line " + std::to_string(line_num));
        }
        if (burst <= 0) {
            throw std::runtime_error("Non-positive burst time in line " + std::to_string(line_num));
        }
        if (priority < 0) {
            throw std::runtime_error("Negative priority in line " + std::to_string(line_num));
        }

        processes.emplace_back(id, arrival, burst, priority);
    }

    if (processes.empty()) {
        throw std::runtime_error("No valid processes found in file");
    }

    return processes;
}

std::vector<Process> InputHandler::generateRandomProcesses(int count,
                                                         int max_arrival,
                                                         int min_burst,
                                                         int max_burst,
                                                         int max_priority) {
    // Validate input parameters
    if (count <= 0) throw std::invalid_argument("Invalid process count");
    if (max_arrival < 0) throw std::invalid_argument("Invalid max arrival time");
    if (min_burst <= 0 || max_burst < min_burst) {
        throw std::invalid_argument("Invalid burst time range");
    }
    if (max_priority < 0) throw std::invalid_argument("Invalid max priority");

    std::vector<Process> processes;
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create distributions
    std::uniform_int_distribution<> arrival_dist(0, max_arrival);
    std::uniform_int_distribution<> burst_dist(min_burst, max_burst);
    std::uniform_int_distribution<> priority_dist(0, max_priority);

    for (int i = 0; i < count; ++i) {
        int arrival = arrival_dist(gen);
        int burst = burst_dist(gen);
        int priority = priority_dist(gen);
        
        processes.emplace_back(i + 1, arrival, burst, priority);
    }

    // Sort by arrival time for consistency
    std::sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });

    return processes;
}