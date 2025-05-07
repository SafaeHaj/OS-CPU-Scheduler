/**
 * @file Process.h
 * @brief Defines the Process class which represents a process to be scheduled
 *
 * This class encapsulates all the information and behaviors of a process in a CPU
 * scheduling simulation, including arrival time, burst time, priority, and runtime states.
 */

 #ifndef PROCESS_H
 #define PROCESS_H
 
 #include <string>
 
 /**
  * @class Process
  * @brief Represents a process to be scheduled by a CPU scheduler
  *
  * The Process class contains all necessary attributes for scheduling simulation,
  * such as arrival time, burst time, priority, and tracks execution metrics like
  * waiting time and turnaround time. It also provides utility methods for process state
  * management and scheduling algorithm implementation.
  */
 class Process {
 public:
     int id;               ///< Unique process identifier
     int arrival_time;     ///< Time at which the process arrives in the system
     int burst_time;       ///< Total CPU time required by the process
     int priority;         ///< Priority value (lower number = higher priority)
     int remaining_time;   ///< Remaining execution time needed
     int waiting_time;     ///< Total time spent waiting
     int turnaround_time;  ///< Total time from arrival to completion
     int completion_time;  ///< Time at which the process completes
     int current_progress; ///< Current execution progress for visualization
     std::string name;     ///< Display name of the process
 
     /**
      * @brief Equality comparison operator
      * @param other The process to compare with
      * @return true if processes have the same ID, false otherwise
      */
     bool operator==(const Process &other) const {
         return id == other.id;
     }
 
     /**
      * @brief Constructor for Process
      * @param id Process identifier
      * @param arrival_time Time at which process arrives
      * @param burst_time Total CPU time required by the process
      * @param priority Priority value (lower = higher priority)
      */
     Process(int id, int arrival_time, int burst_time, int priority);
 
     /**
      * @brief Check if the process has completed execution
      * @return true if process has finished, false otherwise
      */
     bool isDone() const;
 
     /**
      * @brief Advance the process execution by given amount
      * @param amount Amount of time units to advance (default: 1)
      */
     void step(int amount = 1);
 
     /**
      * @brief Get the turnaround time of the process
      * @return Turnaround time (completion time - arrival time)
      */
     int getTurnaroundTime() const;
 
     /**
      * @brief Get the waiting time of the process
      * @return Waiting time (turnaround time - burst time)
      */
     int getWaitingTime() const;
 
     /**
      * @brief Get the arrival time of the process
      * @return Arrival time
      */
     int getArrivalTime() const;
 
     /**
      * @brief Get the burst time of the process
      * @return Burst time
      */
     int getBurstTime() const;
 
     /**
      * @brief Get the priority of the process
      * @return Priority value (lower = higher priority)
      */
     int getPriority() const;
 
     /**
      * @brief Get the ID of the process
      * @return Process ID
      */
     int getId() const;
 
     /**
      * @brief Get the remaining time of the process
      * @return Remaining execution time
      */
     int getRemainingTime() const;
 
     /**
      * @brief Get the completion time of the process
      * @return Completion time
      */
     int getCompletionTime() const;
 
     /**
      * @brief Set the remaining time of the process
      * @param time New remaining time
      */
     void setRemainingTime(int time);
 
     /**
      * @brief Set the completion time of the process
      * @param time Completion time
      */
     void setCompletionTime(int time);
 
     /**
      * @brief Set the turnaround time of the process
      * @param time Turnaround time
      */
     void setTurnaroundTime(int time);
 
     /**
      * @brief Set the waiting time of the process
      * @param time Waiting time
      */
     void setWaitingTime(int time);
 };
 
 #endif // PROCESS_H
