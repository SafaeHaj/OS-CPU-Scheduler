/**
 * @file Scheduler.h
 * @brief Defines the Scheduler abstract base class for CPU scheduling algorithms
 *
 * This abstract class provides the foundation for all CPU scheduling algorithm
 * implementations in the system. It defines the interface for scheduling operations
 * and provides common functionality for metrics calculation.
 */

 #pragma once
 #include <vector>
 #include <string>
 #include "Process.h"
 
 /**
  * @struct Metrics
  * @brief Contains performance metrics of a scheduling algorithm
  *
  * This structure holds various performance metrics calculated after a scheduling
  * simulation run, such as average waiting time, average turnaround time, and CPU
  * utilization.
  */
 struct Metrics {
     float avg_waiting_time = 0.0f;     ///< Average waiting time across all processes
     float avg_turnaround_time = 0.0f;  ///< Average turnaround time across all processes
     float cpu_utilization = 0.0f;      ///< CPU utilization percentage
     int total_idle_time = 0;          ///< Total time CPU was idle
 };
 
 /**
  * @class Scheduler
  * @brief Abstract base class for CPU scheduling algorithms
  *
  * The Scheduler class defines the interface that all scheduling algorithm
  * implementations must adhere to. It also provides common functionality such as
  * metrics calculation and simulation execution.
  */
 class Scheduler {
 protected:
     /** 
      * @brief Timeline of process execution (for Gantt chart)
      * 
      * Each tuple contains: (process ID, start time, end time)
      */
     std::vector<std::tuple<int, int, int>> timeline;
     
     int current_time = 0; ///< Current time in the simulation
 
 public:
     Metrics metrics;                ///< Performance metrics for this scheduler
     std::vector<Process> processes; ///< Processes to be scheduled
 
     /**
      * @brief Virtual destructor for proper cleanup
      */
     virtual ~Scheduler() = default;
 
     /**
      * @brief Get the name of the scheduling algorithm
      * @return String name of the algorithm
      */
     virtual std::string getName() const = 0;
 
     /**
      * @brief Print a Gantt chart of the schedule
      *
      * Displays a visual representation of the schedule showing which process
      * runs at what time.
      */
     virtual void print_gantt_chart() = 0;
     
     /**
      * @brief Perform one step of the scheduling algorithm simulation
      * @return true if simulation is complete, false otherwise
      */
     virtual bool step() = 0;
     
     /**
      * @brief Initialize the simulation
      * @return true if initialization succeeded, false otherwise
      */
     virtual bool init() = 0;
     
     /**
      * @brief Run the complete simulation
      * 
      * This method runs the scheduler and calculates performance metrics.
      */
     void run_simulation();
 
     /**
      * @brief Calculate performance metrics after simulation
      *
      * Calculates metrics like average waiting time, average turnaround time,
      * and CPU utilization based on simulation results.
      */
     void calculate_metrics();
 };
