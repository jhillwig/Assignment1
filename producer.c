// producer.c / producer.cpp
// Operating Systems Fall 2025
// Josh Hillwig
// Explain: 

// Dependencies 
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <signal.h>
  #include <time.h>
  #include <sys/mman.h>
  #include <semaphore.h>
  #include <string.h>

// 2 items allowed to be on table at a given moment
//Defining Shared memory name (the table) and the 3 semaphone patterns
  #define SHM_NAME "/shm_table"
  #define SEM_EMPTY "/sem_empty"
  #define SEM_FULL  "/sem_full"
  #define SEM_MUTEX "/sem_mutex"
  #define TABLE_SIZE 2  

// Creating Table type
  typedef struct {
    int buffer[TABLE_SIZE];
    int in;
    int out;
  } Table;

// Defining the table and some variables for shared memory
  static Table *table;
  static int shm_fd;
  static sem_t *empty, *full, *mutex;
  static volatile sig_atomic_t running = 1;

// Pre-defining helper functions
  int genItem();
  void handleQuit(int);
  void cleanup();

// Main
  int main() {
    //a
      signal(SIGINT, handleQuit);
      srand(time(NULL));

    // Run cleanup() at the end of main then return 0
      cleanup();
      return 0;
  }

// Makes sure a random integer between 0 and 999 is returned
  int genItem() {
    return (rand() % 1000);
  }

// Handeler for Quit
  void handleQuit(int sig) {
    running = 0;
  }

// Closes semaphores and unlinks shared resources
  void cleanup() {
  
  }


