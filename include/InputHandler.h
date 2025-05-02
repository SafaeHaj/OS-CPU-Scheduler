/**
 * @file InputHandler.h
 * @brief Provides utilities for loading and generating processes
 *
 * This file contains utilities for loading processes from files or generating
 * random processes for the CPU scheduling simulation.
 */

 #ifndef INPUT_HANDLER_H
 #define INPUT_HANDLER_H
 
 #include <vector>
 #include <string>
 #include "Process.h"
 
 /**
  * @class InputHandler
  * @brief Utility class for process input handling
  *
  * Provides static methods to read processes from file or generate random
  * processes for simulation.
  */
 class InputHandler {
 public:
     /**
      * @brief Read processes from a file
      * @param filename Path to the file containing process data
      * @return Vector of Process objects
      * 
      * The file should contain one process per line in the format:
      * ID ARRIVAL_TIME BURST_TIME PRIORITY
      */
     static std::vector<Process> readFromFile(const std::string& filename);
     
     /**
      * @brief Generate random processes for simulation
      * @param count Number of processes to generate
      * @param max_arrival Maximum arrival time
      * @param min_burst Minimum burst time
      * @param max_burst Maximum burst time
      * @param max_priority Maximum priority value
      * @return Vector of randomly generated Process objects
      */
     static std::vector<Process> generateRandomProcesses(int count,
                                                       int max_arrival,
                                                       int min_burst,
                                                       int max_burst,
                                                       int max_priority);
 };
 
 #endif // INPUT_HANDLER_H