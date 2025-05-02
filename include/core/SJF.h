/**
 * @file SJF.h
 * @brief Defines the Shortest Job First CPU scheduling algorithm
 *
 * This file contains the implementation of the SJF (Shortest Job First)
 * scheduling algorithm, which prioritizes processes with the shortest
 * burst time.
 */

 #pragma once
 #include "Scheduler.h"
 #include <queue>
 
 /**
  * @class SJF
  * @brief Shortest Job First scheduling algorithm implementation
  *
  * SJF is a non-preemptive scheduling algorithm that selects the process
  * with the shortest burst time for execution when the CPU is available.
  */
 class SJF : public Scheduler {
 private:
     /**
      * @struct SJFComparator
      * @brief Comparison function for the priority queue
      *
      * This comparator ensures that processes with shorter remaining time
      * have higher priority in the queue.
      */
     struct SJFComparator {
         /**
          * @brief Compare two processes based on remaining time
          * @param a First process
          * @param b Second process
          * @return true if a has longer remaining time than b, false otherwise
          */
         bool operator()(const Process* a, const Process* b) const;
     };
 
     /** @brief Priority queue for ready processes sorted by burst time */
     std::priority_queue<Process*, std::vector<Process*>, SJFComparator> ready_queue;
     
     Process* current_process = nullptr; ///< Currently executing process
     size_t next_arrival_idx = 0;        ///< Index of next process to arrive
     bool simulation_started = false;    ///< Flag indicating if simulation has started
 
 public:
     /**
      * @brief Get the name of the algorithm
      * @return String "Shortest Job First"
      */
     std::string getName() const override;
     
     /**
      * @brief Execute the SJF scheduling algorithm
      *
      * Selects the process with shortest burst time when CPU is available.
      */
     void schedule() override;
     
     /**
      * @brief Display the SJF Gantt chart
      */
     void print_gantt_chart() override;
     
     /**
      * @brief Initialize the SJF simulation
      * @return true if initialization succeeded, false otherwise
      */
     bool init() override;
     
     /**
      * @brief Perform one step of the SJF simulation
      * @return true if simulation is complete, false otherwise
      */
     bool step() override;
 };