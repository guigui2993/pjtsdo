#define MAX_SEND_SIZE 2

#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>


typedef struct mymsgbuf
{
    long mtype;
    char mtext[MAX_SEND_SIZE];
}mymsgbuf;


int open_queue(key_t keyval);
void send_message(int qid, mymsgbuf *qbuf, long type, char *text);
void read_message(int qid, mymsgbuf *qbuf, long type);
void remove_queue(int qid);
