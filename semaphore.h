#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include <string.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buf;
};

int open_sem_set(key_t keyval, int numsems);
void init_semaphore(int sid, int semnum, int initval);
void locksem(int sid, int member);
void unlocksem(int sid, int member);
void remove_sem(int sid);


