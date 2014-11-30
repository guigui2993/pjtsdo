#include "share_mem.h"

int open_segment(key_t keyval, int segsize)
{
    int shmid;

    if((shmid = shmget(keyval, segsize, IPC_CREAT|0660)) == -1)
	return(-1);

    return(shmid);
}

int* attach_segment(int shmid)
{
    return((int*)shmat(shmid, 0, 0));
}
/*
void writeshm(int *segptr, int index, int value)
{
    segptr[index] = value;
    printf("(Controler) Wrote %d\n", value);
    fflush(stdout);
}

int readshm(int *segptr, int id, int index)
{
    if(segptr[index] > 0)
	printf("(Philosopher %d) Read %d\n", (id+1), segptr[index]);
    return segptr[index];
}
*/
void remove_shm(int shmid)
{
    shmctl(shmid, IPC_RMID, 0);
    printf("Shared memory segment marked for deletion\n");
}
