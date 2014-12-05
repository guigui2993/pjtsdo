#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Dijkstra.h"

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
	while(!scanf("%d",&total_robot)){
		char tmp;
		while ((tmp = getchar()) != '\n' && tmp != EOF)
			continue;
		printf("error");
	}
    printf("Enter the size of the factory: \n");
    printf("x_size: ");
	while(!scanf("%d",&lane_x)){
		char tmp;
		while ((tmp = getchar()) != '\n' && tmp != EOF)
			continue;
		printf("error");
	}
    printf("y_size: ");
	while(!scanf("%d",&lane_y)){
		char tmp;
		while ((tmp = getchar()) != '\n' && tmp != EOF)
			continue;
		printf("error");
	}
    
    printf("Let's start!\n");
//    sleep(0.5);

    printf("\033[H\033[J");

// DIJKSTRA TESTING

	//int **mat = NULL;
	int size = 5;
	Path *path;
	path = malloc(sizeof(Path));

	path->arr = malloc(size*sizeof(int));
	path->maxSize = size;
	path->size = 0;

	
	int **mat;
	mat = (int**)calloc(size, sizeof(int*));
	for(int i=0; i<size; i++)
		mat[i] = (int*)calloc(size, sizeof(int));
	/*
	for(int i=0;i<size;++i)
		for(int j=0;j<size;++j)
			if(i-j==1||j-1==1)
				mat[i][j] = 1;
				*/
	int maty[5][5] = {{0, 1, 0, 0, 0},{1, 0, 1, 1, 0},{0, 1, 0, 1, 0},{0, 1, 1, 0, 0},{0, 0, 0, 0, 0}};
	
	for(int i=0;i<size;++i)
		for(int j=0;j<size;++j)
			mat[i][j] = maty[i][j];
	
			
	int start = 0;
	int end = 4;
	printf("Dijkstra test unreachable\n");
	dijkstra(mat, size, start, end, path);

	if(path->size==-1)
		printf("node Unreachable\n");
	else{
		for(int i=0;i<path->size;++i)
			printf("%d ", path->arr[i]);
	}

	start = 0;
	end = 3;
	printf("Dijkstra test succeeds and return path\n");
	dijkstra(mat, size, start, end, path);

	if(path->size==-1)
		printf("node Unreachable\n");
	else{
		for(int i=0;i<path->size;++i)
			printf("%d ", path->arr[i]);
	}

	free(path->arr);
	free(path);

    return(0);
}
