#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <vector>
#include <string>
#include "core/Process.h"

class InputHandler
{
public:
    // Read processes from file
    static std::vector<Process> readFromFile(const std::string &filename);

    // Generate random processes
    static std::vector<Process> generateRandomProcesses(int count,
                                                        int max_arrival,
                                                        int min_burst,
                                                        int max_burst,
                                                        int max_priority);
};

#endif // INPUT_HANDLER_H