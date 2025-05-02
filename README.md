# OS CPU Scheduler

This repository contains the first assignment for the Operating Systems course, focusing on CPU scheduling algorithms. It includes implementations of:

- First-Come-First-Served (FCFS)
- Shortest Job First (SJF)
- Priority Scheduling
- Round Robin (RR)
- Round Robin with Priority (RR + Priority)

## Objectives

- Understand and compare scheduling algorithms.
- Implement and simulate their behavior.
- Analyze performance metrics: turnaround time, waiting time, and CPU utilization.

Students: Safae Hajjout & Yahya Mansoub

## Project Structure

```
OS-CPU-Scheduler/
├── include/
│   ├── core/
│   │   ├── FCFS.h       # First-Come-First-Served algorithm
│   │   ├── Priority.h   # Priority scheduling algorithm
│   │   ├── PriorityRR.h # Priority Round Robin algorithm
│   │   ├── RR.h         # Round Robin algorithm
│   │   ├── Scheduler.h  # Base class for all schedulers
│   │   └── SJF.h        # Shortest Job First algorithm
│   ├── InputHandler.h   # Process input utilities
│   └── Process.h        # Process class definition
├── src/
│   ├── core/            # Implementation files for scheduling algorithms
│   ├── main.cpp         # Terminal-based visualization
│   └── InputHandler.cpp # Implementation of input utilities
├── test/                # Test input files
│   └── processes.txt    # Sample process data
├── Makefile             # Build configuration
└── README.md            # Project documentation
```

## Building the Project

To build the project, simply run:

```bash
make
```

This will compile the code and create the executable in the `bin/` directory.

## Running the Scheduler

To run the CPU scheduler visualization:

```bash
./bin/app
```

## Features

### GUI-Based Visualization with SFML C++ Library

### GUI Development Journey

The project initially explored graphical visualization using the SFML C++ library. While early prototypes showed promising results (available in the `gui/` directories), we ultimately prioritized the terminal-based approach for:

- More reliable cross-platform compatibility
- Simplified implementation focusing on algorithm correctness
- Better integration with the core scheduling components
- Enhanced development efficiency

The terminal-based visualization still provides comprehensive visual feedback while maintaining the educational value of the scheduling demonstrations.

### Terminal-Based Visualization

The project includes a terminal-based visualization system that:

1. Displays real-time progress of each process
2. Shows current system time
3. Uses color coding to differentiate processes
4. Displays completion statistics when finished

### Scheduling Algorithms

1. **First-Come-First-Served (FCFS)**
   - Non-preemptive algorithm that schedules processes in order of arrival
   - Simple implementation with predictable behavior

2. **Shortest Job First (SJF)**
   - Non-preemptive algorithm that selects the process with the shortest burst time
   - Optimal for minimizing average waiting time

3. **Priority Scheduling**
   - Non-preemptive algorithm that selects the process with the highest priority (lowest number)
   - Allows important processes to be executed first

4. **Round Robin (RR)**
   - Preemptive algorithm that gives each process a fixed time quantum
   - Ensures fair execution time for all processes

5. **Priority Round Robin**
   - Combined algorithm that uses priority levels with round robin within each level
   - Balances importance and fairness

### Input Methods

The application supports three ways to input processes:

1. **Manual Input**: Enter process details directly
2. **File Input**: Read processes from a file
3. **Random Generation**: Generate random processes with configurable parameters

## Code Documentation

### Process Class

The `Process` class represents a process to be scheduled. It includes:

- Basic attributes: `id`, `arrival_time`, `burst_time`, `priority`
- Runtime tracking: `remaining_time`, `current_progress`
- Performance metrics: `waiting_time`, `turnaround_time`, `completion_time`

Key methods:
- `isDone()`: Checks if the process has completed execution
- `step()`: Advances the execution of the process
- `getTurnaroundTime()`: Returns the turnaround time of the process
- `getWaitingTime()`: Returns the waiting time of the process

### Scheduler Class

`Scheduler` is the abstract base class for all scheduling algorithms. It provides:

- Interface methods that all schedulers must implement
- Common functionality like metrics calculation
- Management of processes and their execution

Key methods:
- `schedule()`: Executes the scheduling algorithm
- `init()`: Initializes the simulation
- `step()`: Performs one step of the simulation
- `calculate_metrics()`: Computes performance metrics

### Algorithm Implementations

Each algorithm extends the base `Scheduler` class and implements:

- The scheduling logic in `schedule()` method
- Step-by-step execution in `step()` method
- Initialization in `init()` method
- Gantt chart visualization in `print_gantt_chart()` method

## Sample Process File Format

The process input file should have the following format:
```
ID ARRIVAL_TIME BURST_TIME PRIORITY
```

Example (`test/processes.txt`):
```
1 0 10 3
2 2 5 2
3 4 8 1
4 6 4 4
5 8 2 5
```

## Performance Metrics

The simulator calculates the following performance metrics:

1. **Average Waiting Time**: Average time processes spend waiting for CPU
2. **Average Turnaround Time**: Average time from arrival to completion
3. **CPU Utilization**: Percentage of time CPU is busy

## Implementation Highlights

- The `step()` method in each scheduler allows for step-by-step visualization
- Priority queues are used to efficiently select the next process in SJF and Priority schedulers
- ANSI escape codes are used for terminal visualization and colorful output
- Comprehensive error handling for input validation

## Known Limitations

- The terminal visualization works best on Unix-based systems (Linux, macOS)
- Very large numbers of processes may crowd the terminal display
- The visualization refresh rate is fixed and not configurable at runtime