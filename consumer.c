// consumer.c / consumer.cpp
// Operating Systems Fall 2025
// Josh Hillwig

// Dependencies
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/mman.h>
#include <semaphore.h>
#include "sharedMemTable.h"

// Defining the table and some variables for shared memory
  static Table *table;
  static int shm_fd;
  static sem_t *empty, *full, *mutex;
  static volatile sig_atomic_t s_running = 1;

// Pre-defining helper functions
  void handleQuit(int);
  void cleanup();

// Main
  int main() {
    // Registering signal handler and randomization for items
      signal(SIGINT, handleQuit);
      srand(time(NULL));

    // Setting up Shared Memory
      shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
      table = mmap(NULL, sizeof(Table), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
      
    // Intialization of Semaphores
      empty = sem_open(SEM_EMPTY, 0);
      full = sem_open(SEM_FULL, 0);
      mutex = sem_open(SEM_MUTEX, 0);

    // Printing Process Initiation
      printf("[Consumer]: Starting consumption...\n");

    // While loop for iterations
      int loop_it = 0;
      while(s_running && (loop_it < ITERATIONS)) {
        // Waits because the there is a process being ran so no spots are open (Decrement for semaphores)
          sem_wait(full);
          sem_wait(mutex);

        // Putting item onto table
          table->buffer[table->out] = item;
          printf("\n[Consumer]: Consumed %d from position %d\n", item, table->out);
          table->out = (table->out + 1) % TABLE_SIZE;

        // Releasing the mutex and increments empty due to free slots (Increment for semaphores)
          sem_post(mutex);
          sem_post(empty);
        
        // Increasing iterations and 
          loop_it++;
          sleep((rand() % 2) + 1);
      }

    // Run cleanup() at the end of main then return 0
      cleanup();
      return 0;
  }

// Handeler for Quit
  void handleQuit(int signal) {
    s_running = 0;
  }

// Unmaping/Unlinking and Closing(tables/semaphores)
  void cleanup() {
    // Printing cleaning messsage  
      printf("\n[Consumer]: Cleaning up...\n");

    // Unmapping/Closing table
      munmap(table, sizeof(Table));
      close(shm_fd);

    // Closing semaphores
      sem_close(empty);
      sem_close(full);
      sem_close(mutex);

    // Printing Exit message
      printf("[Consumer]: Exiting...\n");
  }
