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
 
 /**
  * @class FCFS
  * @brief First-Come-First-Served scheduling algorithm implementation
  *
  * FCFS is the simplest scheduling algorithm, executing processes in the order
  * they arrive in the ready queue without preemption.
  */
 class FCFS : public Scheduler {
 private:
     size_t current_process_idx = 0;     ///< Index of currently executing process
     bool simulation_started = false;    ///< Flag indicating if simulation has started
     Process* current_process = nullptr; ///< Pointer to the currently executing process
 
 public:
     /**
      * @brief Get the name of the algorithm
      * @return String "First Come First Served"
      */
     std::string getName() const override;
     
     /**
      * @brief Execute the FCFS scheduling algorithm
      *
      * Sorts processes by arrival time and executes them in that order.
      */
     void schedule() override;
     
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