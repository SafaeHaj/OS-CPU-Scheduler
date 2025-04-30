#ifndef PROCESS_H
#define PROCESS_H

class Process {
  public:
  int id;
  int arrival_time;
  int burst_time;
  int priority;
  int remaining_time;
  int waiting_time;
  int turnaround_time;
  int completion_time;

  Process(int id, int arrival_time, int burst_time, int priority)
      : id(id), arrival_time(arrival_time), burst_time(burst_time), priority(priority),
        remaining_time(burst_time), waiting_time(0), turnaround_time(0), completion_time(0) {}
};



#endif // PROCESS_H

