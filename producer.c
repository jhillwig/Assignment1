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
      
    // Intialization of Semaphores

    // Printing Process Initiation

    // While loop for iterations

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

      printf("[Producer]: Exiting cleanly...\n");
  }


