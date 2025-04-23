#include "InputHandler.h"
#include <fstream>
#include <sstream>
#include <random>
#include <stdexcept>

std::vector<Process> InputHandler::readFromFile(const std::string& filename) {
    std::vector<Process> processes;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id, at, bt, prio;
        
        if (!(iss >> id >> at >> bt >> prio)) {
            throw std::runtime_error("Invalid input format in file");
        }

        if (at < 0 || bt <= 0 || prio < 0) {
            throw std::runtime_error("Invalid process parameters");
        }

        processes.emplace_back(id, at, bt, prio);
    }
    return processes;
}

std::vector<Process> InputHandler::generateRandomProcesses(int count,
                                                          int max_arrival,
                                                          int min_burst,
                                                          int max_burst,
                                                          int max_priority) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<Process> processes;

    std::uniform_int_distribution<> arrival_dist(0, max_arrival);
    std::uniform_int_distribution<> burst_dist(min_burst, max_burst);
    std::uniform_int_distribution<> priority_dist(0, max_priority);

    for (int i = 0; i < count; ++i) {
        processes.emplace_back(
            i + 1,                     // ID
            arrival_dist(gen),         // Arrival time
            burst_dist(gen),           // Burst time
            priority_dist(gen)         // Priority
        );
    }
    return processes;
}