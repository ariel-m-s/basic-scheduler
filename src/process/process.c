#include "process.h"

#include <stdlib.h>


// State enumeration
enum state
{
  Ready,
  Running,
  Waiting,
  Finished,
};

// Burst type enumeration
enum burst_type
{
  CPU,
  IO,
};


// Burst structure
struct burst
{
  BurstType type;
  int duration;
};

// Process structure
struct process
{
  char *name;
  int pid; // process id
  int priority;
  int t0; // start time
  Burst *bursts;
  int exec_time; // execution time
  State state; // process state
};


// Initializes a burst
Burst *new_burst(BurstType type, int duration)
{
  Burst *burst = calloc(1, sizeof(Burst));
  burst->type = type;
  burst->duration = duration;

  return burst;
}

// Initializes a process
Process *new_process(char *name, int pid, int priority, int t0, int n, int *durations)
{
  Process *process = calloc(1, sizeof(Process));

  process->name = name;
  process->pid = pid;
  process->priority = priority;
  process->t0 = t0;
  process->exec_time = 0;
  process->state = Ready;

  process->bursts = calloc(n, sizeof(Burst));
  for (int i = 0; i < n; i++)
  {
    BurstType type = i % 2 ? IO : CPU;
    Burst *burst = new_burst(type, durations[i]);
    process->bursts[i] = *burst;
    free(burst);
  }

  return process;
}

// Frees a process
void free_process(Process *process)
{
  free(process->name);
  free(process->bursts);
  free(process);
}