#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <limits>
#include <iomanip>
#include <unistd.h>
#include "utils/Drawer.h"
#include "utils/Selector.h"
#include "utils/Comparator.h"
// Forward declarations

int main()
{
    // Check if running in terminal and relaunch if not
    if (!isatty(STDIN_FILENO))
    {
        system("gnome-terminal -- ./bin/app"); // Linux
        return 0;
    }
    bool runAgain = true;
    do
    {
        try
        {
            std::cout << "\033[2J\033[H";

            int operation = Selector::selectOperationMode();

            if (operation == 1)
            {
                // Get scheduler
                auto scheduler = Selector::selectSchedulingAlgorithm();

                // Get processes based on input method
                scheduler->processes = Selector::selectInputMethod();

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
                        Drawer::drawProgressBar(scheduler->processes[j], width, j + 4);
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
                    Drawer::drawFinishedTable(finished_processes, 4, 70);

                    // Take one step in simulation
                    done = scheduler->step();
                    current_time++;

                    // Wait a bit
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
                }

                // Calculate metrics
                scheduler->calculate_metrics();

                // Move cursor below all progress bars
                int cursorPosition = scheduler->processes.size() + 5;
                std::cout << "\033[" << cursorPosition << ";0H";
                std::cout << "\nSimulation complete!\n";

                // Show cursor again
                std::cout << "\033[?25h";

                // Draw final metrics table
                Drawer::drawFinalMetrics(*scheduler, scheduler->processes.size() + 7);

                // Add some spacing before showing cursor
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::cout << "\n\nPress any key to exit...";
                std::cin.ignore();
                std::cout << "\033[?25h";
            }
            else
            {
                Comparator::runComparativeAnalysis();
            }
            // Modified exit prompt to continue
            std::cout << "\n\033[1;36m"; // Cyan color
            char choice;
            std::cout << "Would you like to run another simulation? (y/n): ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            runAgain = (tolower(choice) == 'y');
        }
        catch (const std::exception &e)
        {
            std::cerr << "\nError: " << e.what() << "\n";
            std::cout << "Would you like to try again? (y/n): ";
            char choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            runAgain = (tolower(choice) == 'y');
        }
    } while (runAgain);
    std::cout << "\033[0mThank you for using the scheduler simulator!\n";
    return 0;
}
