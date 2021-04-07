#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
void forkexample() 
{ 
    // child process because return value zero 
    if (fork() == 0) 
        printf("I'm the Child!\n"); 
  
    // parent process because return value non-zero. 
    else
        printf("I'm the Parent!\n"); 
} 
int main() 
{ 
    forkexample(); 
    return 0; 
}

