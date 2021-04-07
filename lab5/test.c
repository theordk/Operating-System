#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/shm.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t * mutex1;
sem_t * mutex2;
//sem_t * mutex3;
int pid1, pid2;

void *mythread1(void *arg){
    
    sem_wait(mutex1);
    pid1 = fork();
    if (pid1 == 0){
        execlp("chrome", "chrome", NULL);
        exit(0);
    }
    
       sem_post(mutex2); 
    
    return NULL;
}

void *mythread2(void *arg){
    
   sem_wait(mutex2);
    pid2 = fork();
    if (pid2 == 0){
        execlp("safari", "safari", NULL);
        exit(0);
    }
    
    return NULL;
}

/* void *mythread3(void *arg){
    
    return NULL;
}  */

int main (int argc, char *argv[]) {

    int iret1, iret2/* , iret3 */;
    pthread_t thread1, thread2/* , thread3 */;

    mutex1 = sem_open("test11", O_CREAT, S_IRUSR | S_IWUSR, 1);
    mutex2 = sem_open("test22", O_CREAT, S_IRUSR | S_IWUSR, 0);
    //mutex3 = sem_open("test3", O_CREAT, S_IRUSR | S_IWUSR, 0);

    iret1 = pthread_create(&thread1, NULL, mythread1, NULL);
    if(iret1) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1); 
        exit(EXIT_FAILURE);
    }

    iret2 = pthread_create(&thread2, NULL, mythread2, NULL);
    if(iret2) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2); 
        exit(EXIT_FAILURE);
    }

    /* iret3 = pthread_create(&thread3, NULL, mythread3, NULL);
    if(iret3) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret3); 
        exit(EXIT_FAILURE);
    } */
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    //pthread_join(thread3, NULL);

    return 0;
}


