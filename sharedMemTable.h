// sharedMemTable.h / sharedMemTable.hpp
// Operating Systems Fall 2025
// Josh Hillwig

#ifndef SHARED_MEM_TABLE_H
#define SHARED_MEM_TABLE_H

// Dependencies 
#include <semaphore.h>

// Defining Shared memory name (the table) and Table size (ONLY two items at once)
#define TABLE_SIZE 2
#define SHM_NAME "shm_table"

// Defining the 3 Semaphore patterns and Iterations (Running program for examples)
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL  "/sem_full"
#define SEM_MUTEX "/sem_mutex"
#define ITERATIONS 25

// Creating Table type
  typedef struct {
    int buffer[TABLE_SIZE];
    int in;
    int out;
  } Table;


#endif
