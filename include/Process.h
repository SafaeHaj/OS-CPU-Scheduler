#ifndef PROCESS_H
#define PROCESS_H


class Process {
  private:
  int id;
  int arrival_time;
  int burst_time;
  int priority;
  int remaining_time;
  int waiting_time;
  int turnaround_time;
  int completion_time;

  


  public:


  // Getters 

    int getId() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriority() const;
    int getRemainingTime() const;
    int getWaitingTime() const;
    int getTurnaroundTime() const;
    int getCompletionTime() const;
    void setRemainingTime(int rt);
    void updateWaitingTime(int wt); 
    void setCompletionTime(int ct);
    void setTurnaroundTime(int tt); 
    void setWaitingTime(int wt);

    Process(int id, int arrival_time, int burst_time, int priority);


};



#endif // PROCESS_H