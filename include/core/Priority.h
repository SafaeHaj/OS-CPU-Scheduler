/**
 * @file Priority.h
 * @brief Defines the Priority CPU scheduling algorithm
 *
 * This file contains the implementation of the Priority scheduling algorithm,
 * which selects processes based on their priority value.
 */

 #pragma once
 #include "Scheduler.h"
 #include <queue>
 
 /**
  * @class Priority
  * @brief Priority scheduling algorithm implementation
  *
  * The Priority scheduler is a non-preemptive algorithm that selects the process
  * with the highest priority (lowest priority number) to execute next.
  */
 class Priority : public Scheduler {
 private:
     /**
      * @struct PriorityComparator
      * @brief Comparison function for the priority queue
      *
      * This comparator ensures that processes with higher priority (lower priority number)
      * have higher precedence in the queue.
      */
     struct PriorityComparator {
         /**
          * @brief Compare two processes based on priority
          * @param a First process
          * @param b Second process
          * @return true if a has lower priority than b, false otherwise
          */
         bool operator()(const Process* a, const Process* b) const;
     };
 
     /** @brief Priority queue for ready processes sorted by priority */
     std::priority_queue<Process*, std::vector<Process*>, PriorityComparator> ready_queue;
     
     Process* current_process = nullptr; ///< Currently executing process
     size_t next_arrival_idx = 0;        ///< Index of next process to arrive
     bool simulation_started = false;    ///< Flag indicating if simulation has started
 
 public:
     /**
      * @brief Get the name of the algorithm
      * @return String "Priority Scheduling"
      */
     std::string getName() const override;

     /**
      * @brief Display the Priority Scheduling Gantt chart
      */
     void print_gantt_chart() override;
     
     /**
      * @brief Initialize the Priority simulation
      * @return true if initialization succeeded, false otherwise
      */
     bool init() override;
     
     /**
      * @brief Perform one step of the Priority simulation
      * @return true if simulation is complete, false otherwise
      */
     bool step() override;
 };
