/**
 * A simple pthread program illustrating POSIX scheduling.
 *
 * Figure 6.8
 *
 * To compile:
 *
 *      gcc helloToMany.c -o helloToMany -lpthread
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

/* the thread runs in this function */
void *runner(void *param);

main(int argc, char *argv[]){
        srand(time(NULL));
        int i, scope;

        /*printf("Please enter the number of threads you wish\n");

        if( argc < 2 ) {
                printf("The argument supplied is %s\n", argv[1]);
        }*/

        pthread_t tid[NUM_THREADS];     //the thread identifier 
        pthread_attr_t attr;            // set of attributes for the thread 

        // get the default attributes
        pthread_attr_init(&attr);

        // first inquire on the current scope 
        if (pthread_attr_getscope(&attr,&scope) != 0)
                fprintf(stderr, "Unable to get scheduling scope.\n");
        else {
                if (scope == PTHREAD_SCOPE_PROCESS)
                        printf("PTHREAD_SCOPE_PROCESS\n");
                else if (scope == PTHREAD_SCOPE_SYSTEM)
                        printf("PTHREAD_SCOPE_SYSTEM\n");
                else
                        fprintf(stderr,"Illegal scope value.\n");
        }

        //set the scheduling algorithm to PCS or SCS
        if (pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM) != 0)
                printf("unable to set scheduling policy.\n");

        // create the threads
        for (i = 0; i < NUM_THREADS; i++){
                printf("I am thread %ld. Created new thread (%d) in iteration %d...\n", rand()%10,i+1,i);
                pthread_create(&tid[i],&attr,runner,(void *)i);
                if(i%5==0){
                        sleep(1*1000);
                }

        }
        //Now join on each thread
        for (i = 0; i < NUM_THREADS; i++)
                pthread_join(tid[i], NULL);

}

//The thread will begin control in this function.
void *runner(void *param)
{
        // do some work ...
        long tid;
        tid = (long)param;
        printf("Hello World! It´s me, thread: #%ld !\n",tid+1);

        pthread_exit(0);
}
