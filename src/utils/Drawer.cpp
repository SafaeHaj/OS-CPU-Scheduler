#include "utils/Drawer.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <limits>
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

void Drawer::drawProgressBar(const Process &process, int width, int line)
{
    float fraction = float(process.current_progress) / float(process.burst_time);
    int filled = int(fraction * width);
    std::string color = COLORS[process.id % 6];

    // Move cursor to specific line
    std::cout << "\033[" << line << ";0H";

    // Draw the bar with color
    std::cout << color << "Process " << std::setw(3) << process.name << " [";
    for (int i = 0; i < filled; ++i)
        std::cout << "█";
    for (int i = filled; i < width; ++i)
        std::cout << " ";
    std::cout << "] " << int(fraction * 100) << "%" << RESET;
    std::cout.flush();
}

void Drawer::drawFinalMetrics(const Scheduler &scheduler, int startLine)
{
    std::cout << "\033[" << startLine << ";0H";
    std::cout << "┌────────────────────────────┬──────────────────┐\n";
    std::cout << "│         Metric             │      Value       │\n";
    std::cout << "├────────────────────────────┼──────────────────┤\n";
    std::cout << "│ Average Turnaround Time    │ "
              << std::setw(16) << std::fixed << std::setprecision(2)
              << scheduler.metrics.avg_turnaround_time << " │\n";
    std::cout << "│ Average Waiting Time       │ "
              << std::setw(16) << std::fixed << std::setprecision(2)
              << scheduler.metrics.avg_waiting_time << " │\n";
    std::cout << "│ CPU Utilization (%)        │ "
              << std::setw(16) << std::fixed << std::setprecision(2)
              << scheduler.metrics.cpu_utilization << " │\n";
    std::cout << "└────────────────────────────┴──────────────────┘\n";
}

void Drawer::drawFinishedTable(const std::vector<Process> &finished, int startLine, int startCol)
{

    const std::string headerColor = "\033[1;36m"; // Cyan
    const std::string reset = "\033[0m";

    std::cout << "\033[" << startLine << ";" << startCol << "H";
    std::cout << headerColor << "┌───────────────┬───────────────┬──────────────┐" << reset << "\n";

    std::cout << "\033[" << startLine + 1 << ";" << startCol << "H";
    std::cout << headerColor << "│" << reset << " Finished Proc "
              << headerColor << "│" << reset << " Turnaround    "
              << headerColor << "│" << reset << " Waiting Time "
              << headerColor << "│" << reset << "\n";

    std::cout << "\033[" << startLine + 2 << ";" << startCol << "H";
    std::cout << headerColor << "├───────────────┼───────────────┼──────────────┤" << reset;

    for (size_t i = 0; i < finished.size(); ++i)
    {
        std::cout << "\033[" << startLine + 3 + i << ";" << startCol << "H";
        std::cout << headerColor << "│" << reset << " P" << std::left << std::setw(12) << finished[i].id
                  << headerColor << " │ " << reset << std::setw(13) << finished[i].getTurnaroundTime()
                  << headerColor << " │ " << reset << std::setw(12) << finished[i].getWaitingTime()
                  << headerColor << " │" << reset;
    }

    if (!finished.empty())
    {
        std::cout << "\033[" << startLine + 3 + finished.size() << ";" << startCol << "H";
        std::cout << headerColor << "└───────────────┴───────────────┴──────────────┘" << reset;
    }
    std::cout.flush();
}

void Drawer::displayComparativeResults(const std::vector<std::pair<std::string, Metrics>> &results, int processCount)
{
    const std::string headerColor = "\033[1;36m";
    const std::string reset = "\033[0m";
    const std::string rowColor = "\033[38;5;255m";

    // Clear screen and set cursor position
    std::cout << "\033[2J\033[H";

    std::cout << headerColor
              << "┌──────────────────────────────┬────────────────┬────────────────┬──────────────────┐\n"
              << "│          Algorithm           │ Avg Turnaround │  Avg Waiting   │ CPU Utilization  │\n"
              << "├──────────────────────────────┼────────────────┼────────────────┼──────────────────┤\n"
              << reset;

    for (const auto &[name, metrics] : results)
    {
        std::string formattedName = name;
        if (formattedName.length() > 26)
        {
            formattedName = formattedName.substr(0, 23) + "...";
        }

        printf("%s│ %-28s │ %14.2f │ %14.2f │ %15.2f%% │\n",
               rowColor.c_str(),
               formattedName.c_str(),
               metrics.avg_turnaround_time,
               metrics.avg_waiting_time,
               metrics.cpu_utilization);
    }

    std::cout << headerColor
              << "└──────────────────────────────┴────────────────┴────────────────┴──────────────────┘\n"
              << reset;

    // Dynamic observations
    std::cout << "\n\n\033[1;35mAnalysis Summary (" << processCount << " processes):\033[0m\n";
    std::cout << "• \033[1;32mBest Turnaround Time:\033[0m "
              << std::min_element(results.begin(), results.end(),
                                  [](auto &a, auto &b)
                                  { return a.second.avg_turnaround_time < b.second.avg_turnaround_time; })
                     ->first
              << "\n";
    std::cout << "• \033[1;32mBest Waiting Time:\033[0m "
              << std::min_element(results.begin(), results.end(),
                                  [](auto &a, auto &b)
                                  { return a.second.avg_waiting_time < b.second.avg_waiting_time; })
                     ->first
              << "\n";
    std::cout << "• \033[1;32mBest CPU Utilization:\033[0m "
              << std::max_element(results.begin(), results.end(),
                                  [](auto &a, auto &b)
                                  { return a.second.cpu_utilization < b.second.cpu_utilization; })
                     ->first
              << "\n";

    std::cout << "\n\033[1;35mKey Characteristics:\033[0m\n";
    std::cout << "  - FCFS: Simple but sensitive to arrival order\n";
    std::cout << "  - SJF: Optimal for waiting time (needs future knowledge)\n";
    std::cout << "  - Priority: Risk of starvation for low-priority processes\n";
    std::cout << "  - RR: Fair but sensitive to quantum size\n";
    std::cout << "  - PriorityRR: Hybrid approach balancing priorities and fairness\n";
}
