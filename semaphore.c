#include "semaphore.h"

int open_sem_set(key_t keyval, int numsems)
{
    int sid;

    if(!numsems)
	return(-1);
    
    printf("Attempting to create new semaphore set with %d members\n", numsems);

    if((sid = semget(keyval, numsems, IPC_CREAT|0660)) == -1)
	return(-1);
  
    return(sid);
}

void init_sem(int sid, int semnum, int initval)
{
    union semun semopts;
    
    semopts.val = initval;
    semctl(sid, semnum, SETVAL, semopts);
}

void locksem(int sid, int member)
{
    struct sembuf sem_lock = {member,-1,0};

    if((semop(sid, &sem_lock, 1)) == -1)
    {
	fprintf(stderr,"Wait failed\n");
	exit(1);
    }
}

void unlocksem(int sid, int member)
{
    struct sembuf sem_unlock = {member,1,0};

    if((semop(sid, &sem_unlock, 1)) == -1)
    {
	fprintf(stderr,"Signal failed\n");
	exit(1);
    }
}

void remove_sem(int sid)
{
    semctl(sid, 0, IPC_RMID, 0);
    printf("Semaphore set marked for deletion\n");
}
