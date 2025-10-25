# Assignment1
Assignment 1 for Operating System Kent State

### Header and Source files
You will need `sharedTable.h`, `producer.c`, and `consumer.c`

## Execution
### Compiling
```
gcc producer.cpp  -pthread -lrt -o producer
gcc consumer.cpp  -pthread -lrt -o consumer
```

### Running
```
./producer & ./consumer 
```

## Program Description
### Producer & Consumer
`producer` generates the random integers from 0 to 999 simulating the items on the table. After running it a number of times ('ITERATIONS' in 'sharedTable.h'), the program will exit and call 'cleanup'. This unmaps the table, unlinks the semaphores, and then closes them.

`consumer` consumes the random items put on the table by `producer`. After running it a number of times ('ITERATIONS' in 'sharedTable.h'), the program will exit and call 'cleanup'. This unmaps the table and then closes the semaphores and the table.


### Expected Output
Expected output should look something like this
![Expected Output](<img width="854" height="396" alt="Screenshot 2025-10-24 194607" src="https://github.com/user-attachments/assets/97f5b4ab-4186-4c8a-8d57-6edd5d8d808c"/>)
