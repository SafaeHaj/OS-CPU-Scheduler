/**
 * @file RR.h
 * @brief Defines the Round Robin CPU scheduling algorithm
 *
 * This file contains the implementation of the Round Robin scheduling algorithm,
 * which allocates each process a fixed time slice in a cyclic manner.
 */

 #pragma once
 #include "Scheduler.h"
 #include <queue>
 
 /**
  * @class RR
  * @brief Round Robin scheduling algorithm implementation
  *
  * The Round Robin scheduler is a preemptive algorithm that allocates each process
  * a fixed time quantum, cycling through all ready processes.
  */
 class RR : public Scheduler {
 private:
     int time_quantum;                 ///< Time quantum for each process
     std::queue<Process*> ready_queue; ///< Queue of ready processes
     Process* current_process = nullptr; ///< Currently executing process
     int quantum_used = 0;              ///< Time used in current quantum
     size_t next_arrival_idx = 0;       ///< Index of next process to arrive
 
 public:
     /**
      * @brief Constructor for RR scheduler
      * @param quantum Time quantum to use for scheduling
      */
     RR(int quantum);
     
     /**
      * @brief Get the name of the algorithm
      * @return String "Round Robin (TQ=X)" where X is the time quantum
      */
     std::string getName() const override;
     
     /**
      * @brief Execute the Round Robin scheduling algorithm
      */
     void schedule() override;
     
     /**
      * @brief Display the Round Robin Gantt chart
      */
     void print_gantt_chart() override;
     
     /**
      * @brief Initialize the Round Robin simulation
      * @return true if initialization succeeded, false otherwise
      */
     bool init() override;
     
     /**
      * @brief Perform one step of the Round Robin simulation
      * @return true if simulation is complete, false otherwise
      */
     bool step() override;
 };