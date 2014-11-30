#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <ctype.h>
#include <string.h>


#include "msg_queue.h"
#include "semaphore.h"
#include "share_mem.h"
#include "factory.h"
*/

int main()
{


    int lane_x, lane_y;
    int robot_id, total_robot;
    
    printf("\033[H\033[J");
    printf("Game of robot factory:\n");
    printf("______________________\n\n");
    printf("Write rules...\n");
    printf("Press enter to start\n");
    getchar();
    printf("\033[H\033[J");
    printf("Game of robot factory:\n");
    printf("______________________\n\n");
    printf("Enter the number of robots moving in the factory: ");
    scanf("%d",&total_robot);
    printf("Enter the size of the factory: \n");
    printf("x_size: ");
    scanf("%d",&lane_x);
    printf("y_size: ");
    scanf("%d",&lane_y);
    
    printf("Let's start!\n");
    sleep(0.5);

    printf("\033[H\033[J");

    return(0);
}
