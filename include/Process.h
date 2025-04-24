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
  bool is_completed;

  Process(int id, int at, int bt, int prio);

  void execute(); // simulate process execution, can elaborate it later on
};
#endif // PROCESS_H