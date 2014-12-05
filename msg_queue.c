#include "msg_queue.h"

int open_queue(key_t keyval)
{
    int qid;

    if((qid = msgget(keyval, IPC_CREAT|0660)) == -1)
	return(-1);
    
    return(qid);
}

void send_message(int qid, mymsgbuf *qbuf, long type, char *text)
{
    qbuf->mtype = type;
    strcpy(qbuf->mtext, text);
    
    if(msgsnd(qid, qbuf, strlen(qbuf->mtext)+1, 0) == -1)
    {
	perror("msgsnd");
	exit(1);
    }
}

void read_message(int qid, mymsgbuf *qbuf, long type)
{
    qbuf->mtype = type;

    msgrcv(qid, qbuf, MAX_SEND_SIZE, type, 0);
}

void remove_queue(int qid)
{
    if(msgctl(qid, IPC_RMID, 0) == -1)
    {
	perror("msgctl");
	exit(1);
    }
    printf("Message queue marked for deletion\n");
}
