/**
 * @file PriorityRR.h
 * @brief Defines the Priority Round Robin CPU scheduling algorithm
 *
 * This file contains the implementation of the Priority Round Robin scheduling
 * algorithm, which combines priority scheduling with round robin time slicing.
 */

 #pragma once
 #include "Scheduler.h"
 #include <queue>
 #include <vector>
 #include <map>
 
 /**
  * @class PriorityRR
  * @brief Priority Round Robin scheduling algorithm implementation
  *
  * The Priority Round Robin scheduler combines priority scheduling with round robin.
  * It uses round robin for processes of the same priority level, and prioritizes
  * processes with higher priority (lower priority number).
  */
 class PriorityRR : public Scheduler {
 private:
     int time_quantum;    ///< Time quantum for each process
     
     /** @brief Map from priority level to queue of processes at that priority */
     std::map<int, std::queue<Process*>> priority_queues;
     
     int current_priority = -1;         ///< Current priority level being serviced
     Process* current_process = nullptr; ///< Currently executing process
     int quantum_used = 0;              ///< Time used in current quantum
     size_t next_arrival_idx = 0;       ///< Index of next process to arrive
     bool simulation_started = false;   ///< Flag indicating if simulation has started
     
     /**
      * @brief Find the highest priority level with ready processes
      * @return Highest priority level, or -1 if no processes are ready
      */
     int findHighestPriorityQueue() const;
 
 public:
     /**
      * @brief Constructor for PriorityRR scheduler
      * @param quantum Time quantum to use for scheduling
      */
     PriorityRR(int quantum);
     
     /**
      * @brief Get the name of the algorithm
      * @return String "Priority Round Robin (TQ=X)" where X is time quantum
      */
     std::string getName() const override;

     /**
      * @brief Display the Priority Round Robin Gantt chart
      */
     void print_gantt_chart() override;
     
     /**
      * @brief Initialize the Priority Round Robin simulation
      * @return true if initialization succeeded, false otherwise
      */
     bool init() override;
     
     /**
      * @brief Perform one step of the Priority Round Robin simulation
      * @return true if simulation is complete, false otherwise
      */
     bool step() override;
 };
