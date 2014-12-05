#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>

int open_segment(key_t keyval, int segsize);
int* attach_segment(int shmid);
void writeshm(int *segptr, int index, int value);
int readshm(int *segptr, int id, int index);
void remove_shm(int shmid);

