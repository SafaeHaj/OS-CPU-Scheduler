# CPU Scheduler Simulator

A comprehensive terminal-based visualization tool for understanding and comparing CPU scheduling algorithms. This project simulates popular CPU scheduling algorithms with real-time progress visualization, metrics calculation, and comparative analysis features.

![CPU Scheduler Visualization](https://github.com/your-username/OS-CPU-Scheduler/raw/main/screenshots/visualization.png)

## Table of Contents

- Features
- Project Structure
- Scheduling Algorithms
- Installation
- Usage
- Input Methods
- Performance Metrics
- Implementation Details
- Contributing
- License

## Features

- **Interactive Visualization**: Terminal-based real-time visualization of process execution
- **Multiple Scheduling Algorithms**:
  - First Come First Served (FCFS)
  - Shortest Job First (SJF)
  - Priority Scheduling
  - Round Robin (RR) with customizable time quantum
  - Priority Round Robin (Priority + RR hybrid)
- **Detailed Metrics**: Calculation and display of important performance metrics
- **Comparative Analysis**: Ability to run and compare all algorithms on the same process set
- **Flexible Input Methods**:
  - Read process data from files
  - Generate random processes with configurable parameters
  - Manually enter process details
- **Colorful Interface**: ANSI color-coded visualization for easier understanding

## Project Structure

```
OS-CPU-Scheduler/
├── include/                 # Header files
│   ├── core/                # Core scheduler implementation
│   │   ├── FCFS.h           # First Come First Served
│   │   ├── Priority.h       # Priority Scheduling
│   │   ├── PriorityRR.h     # Priority Round Robin
│   │   ├── Process.h        # Process representation
│   │   ├── RR.h             # Round Robin
│   │   ├── Scheduler.h      # Base scheduler
│   │   └── SJF.h            # Shortest Job First
│   └── utils/               # Utility classes
│       ├── Comparator.h     # Algorithm comparison
│       ├── Drawer.h         # Terminal visualization
│       ├── InputHandler.h   # Process input handling
│       └── Selector.h       # User interface elements
├── src/                     # Source files
│   ├── core/                # Algorithm implementations
│   │   ├── FCFS.cpp
│   │   ├── Priority.cpp
│   │   ├── PriorityRR.cpp
│   │   ├── Process.cpp
│   │   ├── RR.cpp
│   │   ├── Scheduler.cpp
│   │   └── SJF.cpp
│   ├── utils/               # Utility implementations
│   │   ├── Comparator.cpp
│   │   ├── Drawer.cpp
│   │   ├── InputHandler.cpp
│   │   └── Selector.cpp
│   └── main.cpp             # Entry point
├── test/                    # Test files with sample process data
│   ├── 1.txt
│   ├── 2.txt
│   └── 3.txt
├── Makefile                 # Build configuration
└── README.md                # This file
```

## Scheduling Algorithms

### First Come First Served (FCFS)
- Non-preemptive scheduling algorithm
- Processes are executed in the order they arrive
- Simple but can lead to the convoy effect

### Shortest Job First (SJF)
- Non-preemptive scheduling algorithm
- Selects the process with the shortest burst time
- Optimal for minimizing average waiting time
- Requires knowledge of burst time in advance

### Priority Scheduling
- Non-preemptive scheduling algorithm
- Processes are executed based on priority (lower value = higher priority)
- May lead to starvation of low-priority processes

### Round Robin (RR)
- Preemptive scheduling algorithm
- Each process gets a fixed time quantum
- Fair allocation of CPU time but higher context-switching overhead
- Performance depends on time quantum selection

### Priority Round Robin (PriorityRR)
- Hybrid preemptive scheduling algorithm
- Combines priority scheduling with round robin
- Processes with higher priority are serviced first
- Round robin is applied within the same priority level

## Installation

### Prerequisites
- C++17 compatible compiler (GCC 7+ or Clang 5+)
- Linux/UNIX terminal (for ANSI color support)
- GNU Make

### Building from Source

1. Clone the repository:
```bash
git clone https://github.com/your-username/OS-CPU-Scheduler.git
cd OS-CPU-Scheduler
```

2. Compile the project:
```bash
make
```

This will create the executable in the bin directory.

## Usage

### Running the Simulator

```bash
./bin/app
```

### Using the Simulator

1. **Select an operation mode**:
   - Single Algorithm Simulation
   - Comparative Analysis (All Algorithms)

2. **For Single Algorithm Simulation**:
   - Choose one of the scheduling algorithms
   - If selecting Round Robin or Priority Round Robin, specify a time quantum
   - Choose an input method for processes
   - Watch the simulation visualize the algorithm

3. **For Comparative Analysis**:
   - Configure process generation parameters
   - Specify the time quantum for RR-based algorithms
   - View and compare the performance metrics of all algorithms

## Input Methods

### File Input
Provide a text file where each line represents a process with space-separated values:
```
<Process ID> <Arrival Time> <Burst Time> <Priority>
```

Example (`test/1.txt`):
```
0 0 8 2
1 1 4 1
2 2 9 3
3 3 5 2
```

### Random Generation
Configure parameters for random process generation:
- Number of processes
- Maximum arrival time
- Minimum/maximum burst time
- Maximum priority value

### Manual Entry
Enter process details one by one through the terminal interface.

## Performance Metrics

The simulator calculates and displays these metrics:

- **Average Waiting Time**: The average time processes spend waiting in the ready queue
- **Average Turnaround Time**: The average time from process arrival to completion
- **CPU Utilization**: Percentage of time the CPU is busy executing processes

## Implementation Details

### Process Class
Represents a process with attributes like arrival time, burst time, priority, and methods to track its execution state.

### Scheduler Class Hierarchy
- `Scheduler`: Abstract base class defining the common interface
- Algorithm-specific implementations (FCFS, SJF, etc.) that inherit from Scheduler

### Visualization
Uses ANSI escape codes to create a dynamic visualization with:
- Color-coded progress bars for process execution
- Real-time table of completed processes
- Final metrics display

### Simulation Cycle
1. Initialize selected scheduler with processes
2. Step through simulation, updating process states
3. Calculate and display metrics when simulation completes

### doc folder
 the doc folder contain walkthroughs of major folders in the project
 and explanations of the code within it.
 
---

Created by [Safae Hajjout & Yahya Mansoub ] 