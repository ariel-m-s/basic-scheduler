#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

// FUNCTIONS

// Initializes a Node [def]
Node *new_node(Process *process)
{
  Node *node = calloc(1, sizeof(Node));
  node->value = process;
  node->next = NULL;

  return node;
}

// Frees a Node [def]
void free_node(Node *node)
{
  free_process(node->value);
  free(node);
}

// Initializes a Queue [def]
Queue *new_queue()
{
  Queue *queue = calloc(1, sizeof(Queue));

  queue->head = NULL;
  queue->tail = NULL;
  queue->length = 0;

  return queue;
}

// Adds a Process to the tail of a Queue [def]
void add(Queue *queue, Process *process)
{
  Node *node = new_node(process);

  queue->length++;

  // queue is not empty
  if (queue->tail) // === queue->head
  {
    queue->tail->next = node;
  }
  // queue is empty
  else
  {
    queue->head = node;
  }
  queue->tail = node;
}

// Queue not empty ? Pops a Process from the head of a Queue : Pops NULL from a Queue [def]
Process *pop(Queue *queue)
{
  // queue is not empty
  if (queue->head) // === queue->tail
  {

    queue->length--;

    // queue is one node long
    if (queue->head == queue->tail)
    {
      queue->tail = NULL;
    }

    Node *node = queue->head;
    queue->head = node->next;

    Process *process = node->value;

    // free the Node (but don't touch the Process)
    free(node);

    return process;
  }
  // queue is empty
  else
  {
    return NULL;
  }
}

// pop + add [def]
Process *cycle(Queue *queue)
{
  Process *process = pop(queue);
  add(queue, process);

  return process;
}

// Sorts a Queue by Process' priority [def]
void priority_sort(Queue *queue)
{
  Queue *sorted = new_queue();
  Process *process;
  int priority;
  int i;

  while(sorted->length != queue->length)
  {
    for (priority = 127; priority >= 0; priority--)
    {
      for (i = 0; i < queue->length; i++)
      {
        process = cycle(queue);

        if (process->priority == priority)
        {
          add(sorted, process);
        }
      }
    }
  }

  // free the old Nodes (but don't touch the Processes)
  Node *node = queue->head;
  Node *aux_node;
  while(node)
  {
    aux_node = node->next;
    free(node);
    node = aux_node;
  }

  // insert the new (sorted) Nodes
  queue->head = sorted->head;
  queue->tail = sorted->tail;

  // free "sorted" Queue (but don't touch the Nodes)
  free(sorted);
}

// Frees a Queue [def]
void free_queue(Queue *queue)
{
  Node *node = queue->head; // first Node
  Node *aux_node;
  // there are still Nodes to be freed
  while (node)
  {
    aux_node = node->next;
    free_node(node);
    node = aux_node;
  }

  free(queue);
}

// Prints a representation of a Queue [def]
void print_queue(Queue *queue)
{
  Node *node = queue->head; // first Node
  // there are still Nodes to be printed
  while (node)
  {
    printf("NODE '%s'(t0: %d)\n", node->value->name, node->value->t0);
    node = node->next;
  }
}
