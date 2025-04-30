#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <vector>
#include <string>
#include "Process.h"

class InputHandler {
public:
    // Read processes from file
    static std::vector<Process> readFromFile(const std::string& filename);
    
    // Generate random processes
    static std::vector<Process> generateRandomProcesses(int count,
                                                      int max_arrival,
                                                      int min_burst,
                                                      int max_burst,
                                                      int max_priority);
    
    // Read input from GUI
    static std::vector<Process> readGUI();
};

#endif // INPUT_HANDLER_H