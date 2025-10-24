// producer.c / producer.cpp
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
  int addItem();
  void handleQuit(int);
  void cleanup();

// Main
  int main() {
    // Registering signal handler and randomization for items
      signal(SIGINT, handleQuit);
      srand(time(NULL));

    // Setting up Shared Memory
      int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
      ftruncate(shm_fd, sizeof(Table));
      table = mmap(NULL, sizeof(Table), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
      table->in = 0;
      table->out = 0;
      
    // Intialization of Semaphores
      sem_t *empty = sem_open(SEM_EMPTY, O_CREAT, 0666, TABLE_SIZE);
      sem_t *full = sem_open(SEM_FULL, O_CREAT, 0666, 0);
      sem_t *mutex = sem_open(SEM_MUTEX, O_CREATE, 0666, 1);

    // Printing Process Initiation
      printf("[Producer]: Starting Production...\n");

    // While loop for iterations
      int loop_it = 0;
      while(s_running && (loop_it < ITERATIONS)) {
        // Item Generation
          int item = addItem();

        // Wait until empty slot is availible & for mutual exclusion (Decrement for semaphores)
          sem_wait(empty);
          sem_wait(mutex);

        // Putting item onto table
          table->buffer[table->in] = item;
          printf("[Producer]: Produced %d at position %d\n", item, table->in);
          table->in = (table->in + 1) % TABLE_SIZE;

        // Releasing mutex lock for a new process and signals a new spot is open (Increment for semaphores)
          sem_post(mutex);
          sem_post(full);
        
        // Increasing iterations and 
          loop_it++;
          sleep((rand() % 2) + 1);
      }

    // Run cleanup() at the end of main then return 0
      cleanup();
      return 0;
  }

// Makes sure a random integer between 0 and 999 is returned
  int addItem() {
    return (rand() % 1000);
  }

// Handeler for Quit
  void handleQuit(int signal) {
    s_running = 0;
  }

// Unmaping/Unlinking and Closing(tables/semaphores)
  void cleanup() {
    // Printing cleaning messsage  
      printf("\n[Producer]: Cleaning up...\n");

    // Unmapping/Closing table
      munmap(table, sizeof(Table));
      close(shm_fd);

    // Closing semaphores
      sem_close(empty);
      sem_close(full);
      sem_close(mutex);

    // Unlinking semaphores
      sem_unlink(SEM_EMPTY);
      sem_unlink(SEM_FULL);
      sem_unlink(SEM_MUTEX);
      sem_Unlink(SHM_NAME);

    // Printing Exit message
      printf("[Producer]: Exiting...\n");
  }
