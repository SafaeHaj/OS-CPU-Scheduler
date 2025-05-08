/**
 * @file FCFS.h
 * @brief Defines the First-Come-First-Served CPU scheduling algorithm
 *
 * This file contains the implementation of the FCFS (First-Come-First-Served)
 * scheduling algorithm, which is a non-preemptive algorithm that executes
 * processes in the order they arrive.
 */

 #pragma once
 #include "Scheduler.h"
 #include "Process.h"
 #include <queue>
 
 /**
  * @class FCFS
  * @brief First-Come-First-Served scheduling algorithm implementation
  *
  * FCFS is the simplest scheduling algorithm, executing processes in the order
  * they arrive in the ready queue without preemption.
  */
 class FCFS : public Scheduler {
 private:
      /**
      * @struct FCFSComparator
      * @brief Comparison function for the queue
      *
      * This comparator ensures that processes with lower arrival times
      * have higher precedence in the queue.
      */
     struct FCFSComparator {
        /**
         * @brief Compare two processes based on arrival time
         * @param a First process
         * @param b Second process
         * @return true if a has lower arrival time than b, false otherwise
         */
        bool operator()(const Process* a, const Process* b) const;
    };
     size_t next_arrival_idx = 0;     ///< Index of currently executing process
     bool simulation_started = false;    ///< Flag indicating if simulation has started
     Process* current_process = nullptr; ///< Pointer to the currently executing process
     std::priority_queue<Process*, std::vector<Process*>, FCFSComparator> ready_queue;

 public:
     /**
      * @brief Get the name of the algorithm
      * @return String "First Come First Served"
      */
     std::string getName() const override;
     
     /**
      * @brief Display the FCFS Gantt chart
      */
     void print_gantt_chart() override;
     
     /**
      * @brief Initialize the FCFS simulation
      * @return true if initialization succeeded, false otherwise
      */
     bool init() override;
     
     /**
      * @brief Perform one step of the FCFS simulation
      * @return true if simulation is complete, false otherwise
      */
     bool step() override;
 };
