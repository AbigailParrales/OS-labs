
/*
Lab 4.2 - The Dinning Philosophers Problem
---------------Team:------------------
Diego Ivan Contreras Villegas A00817130
GitUser:divancontreras

Daniela Abigail Parrale Mejía A01228629
GitUser:AbigailParrales

Karol Gutiérrez A01024536
GitUser:karol22
---------------------------------------
Compile with the following command:
gcc dinner.c -o dinner -lpthread

Stop the program with Ctrl+Z

*/

#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
  
#define N 5 
int THINKING=2;
int HUNGRY=1;
int EATING=0;
  
int state[N]; 
int phil[N] = { 0, 1, 2, 3, 4 }; 
  
sem_t mutex; 
sem_t S[N]; 
  
void test(int phnum) { 
    if (state[phnum] == HUNGRY && state[(phnum + 4) % N] != EATING && state[(phnum + 1) % N] != EATING) { 
        // put philosopher into eating state
        state[phnum] = EATING; 
        sleep(2); 
  
        printf("Philosopher %d takes fork #%d and #%d\n", phnum + 1, (phnum + 4) % N + 1, phnum + 1); 
        printf("Philosopher %d is Eating\n", phnum + 1); 
  
        sem_post(&S[phnum]); 
    } 
} 
  
// pick up chopsticks 
void take_fork(int phnum) { 
    sem_wait(&mutex); 
  
    //Set philosopher to hungry 
    state[phnum] = HUNGRY;   
    printf("Philosopher %d is Hungry\n", phnum + 1); 
  
    //Eat if philosopher's neighbours are not eating
    test(phnum); 
    sem_post(&mutex); 
  
    //Wait to be signalled in case the philosopher is unable to eat
    sem_wait(&S[phnum]); 
  
    sleep(1); 
} 
  
//Put down chopsticks 
void put_fork(int phnum) { 
  
    sem_wait(&mutex); 
  
    // state that thinking 
    state[phnum] = THINKING; 
  
    printf("Philosopher %d putting fork #%d and #%d down\n", 
           phnum + 1, (phnum + 4) % N + 1, phnum + 1); 
    printf("Philosopher %d is thinking\n", phnum + 1); 
  
    test((phnum + 4) % N); 
    test((phnum + 1) % N); 
  
    sem_post(&mutex); 
} 
  
void* philospher(void* num) { 
    while (1) { 
        int* i = num; 
        sleep(1); 
        take_fork(*i); 
        sleep(0); 
        put_fork(*i); 
    } 
} 
  
int main(void){ 
    int i; 
    pthread_t thread_id[N]; 
  
    //Init the semaphores 
    sem_init(&mutex, 0, 1); 
    for (i = 0; i < N; i++){  
        sem_init(&S[i], 0, 0); 
    }
  
    for (i = 0; i < N; i++) { 
        //Create processes for the philosopher
        pthread_create(&thread_id[i], NULL, philospher, &phil[i]); 
  
        printf("Philosopher %d is thinking\n", i + 1); 
    } 
  
    for (i = 0; i < N; i++){
        pthread_join(thread_id[i], NULL); 
    }

    return 0;
} 