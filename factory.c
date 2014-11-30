
int** init_screen_matrix(int lane_x, int lane_y, int total_robot)
{
    int **tab;
    int i, j;
    int x_max = 5*lane_x+1;
    int y_max = 5*lane_y+1;
    
    // allocation of the state matrix
    tab = (int**)calloc(y_max, sizeof(int*));
    for(i=0; i<y_max; i++)
	tab[i] = (int*)calloc(x_max, sizeof(int));

    // initialization of the state matrix   
    for(i=0; i<y_max; i++)
    {
	for(j=0; j<x_max; j++)
	{
	    if(i%5 != 0 && j%5 != 0)
		tab[i][j] = -1;
	    else if(i%5 == 0 && j%5 == 0)
		tab[i][j] = 1;
	    else
		tab[i][j] = 0; 
	}
    }

    tab[i-1][0] = total_robot - 1;

    return tab;
}

void print_screen_matrix(int **tab, int lane_x, int lane_y)
{
    int i, j;
    int x_max = 5*lane_x+1;
    int y_max = 5*lane_y+1;
    
    for(i=0; i<y_max; i++)
    {
	for(j=0; j<x_max; j++)
        {
	    if(tab[i][j] == -1)
		printf(" ");
	    else if(tab[i][j] == 1)
		printf("+");
	    else if(tab[i][j] == 0)
		printf(".");
	    else
		printf("%d", tab[i][j]);
	}
	printf("\n");
    }
}

void free_screen_matrix(int **tab, int lane_x, int lane_y)
{
    int i;
    int x_max = 5*lane_x+1;
    int y_max = 5*lane_y+1;

    for(i=0; i<y_max; i++)
	if(x_max>0)
	    free(tab[i]);
    if(y_max>0)
	free(tab);
}

unsigned int** screen_2_state(int **screen_matrix, int lane_x, int lane_y)
{
    int dim = (lane_x+1)*(lane_y+1);
    unsigned int **tab;
    int i,j,k,l;

    // allocation of the state matrix
    tab = (unsigned int**)calloc(dim, sizeof(unsigned int*));
    for(i=0; i<dim; i++)
	tab[i] = (unsigned int*)calloc(dim, sizeof(unsigned int));

    // initialisation of the state matrix
    for(i=0; i<dim; i++)
    {
	for(j=0; j<dim; j++)
	{
            k = (i-i%(lane_x+1))/(lane_x+1) - (j-j%(lane_x+1))/(lane_x+1);
            l = i%(lane_x+1) - j%(lane_x+1);

	    if(k == 0 && l == 0)
		tab[i][j] = 0;
	    else if(((k == 1 || k == -1) && l == 0) || ((l == 1 || l == -1) && k == 0))
		tab[i][j] = 1;
	    else
		tab[i][j] = -1;
	}
    }    
    return tab;
}  

void free_state_matrix(unsigned int **tab, int dim)
{
    int i;

    for(i=0; i<dim; i++)
	if(dim>0)
	    free(tab[i]);
    if(dim>0)
	free(tab);
}

int available_edge(int node_1, int node_2, int **screen_matrix, int lane_x, int lane_y)
{
    int node_1_a, node_1_b, node_2_a, node_2_b;
    int i;
    int status = 0; // -1 == error, 0 == available, 1 == temporarily unavailable, 2 == unavailable  

    if(node_1 < 0 || node_2 < 0)
	return(-1);   // invalid node

    else if(node_1 > (lane_x+1)*(lane_y+1)-1 || node_2 > (lane_x+1)*(lane_y+1)-1)
	return(-1);   // node is out of valid range

    node_1_a = (node_1-node_1%(lane_x+1))/(lane_x+1);
    node_1_b = node_1%(lane_x+1);

    node_2_a = (node_2-node_2%(lane_x+1))/(lane_x+1);
    node_2_b = node_2%(lane_x+1);

    if(node_1_a == node_2_a && node_1_b == node_2_b)
	return(-1);   // same node

    else if( !(((node_2_b - node_1_b == 1 || node_2_b - node_1_b == -1) && node_2_a == node_1_a) || ((node_2_a - node_1_a == 1 || node_2_a - node_1_a == -1) && node_2_b == node_1_b)) )
	return(-1);   // the nodes aren't adjacent

    else if((node_2_a - node_1_a) == 1)  
    {
	for(i=node_1_a+1; i<node_1_a+5; i++)
        {
	    if(screen_matrix[i][5*node_1_b] == 2)
		return(1);  // temporarily unavailable
	    else if(screen_matrix[i][5*node_1_b] == -1)
		return(2);  // unavailable
        }
    }

    else if((node_2_a - node_1_a) == -1)
    {
	for(i=node_2_a+1; i<node_2_a+5; i++)
        {
	    if(screen_matrix[i][5*node_1_b] == 2)
		return(1);  // temporarily unavailable
	    else if(screen_matrix[i][5*node_1_b] == -1)
		return(2);  // unavailable
        }
    }

    else if((node_2_b - node_1_b) == 1)  
    {
	for(i=node_1_b+1; i<node_1_b+5; i++)
        {
	    if(screen_matrix[5*node_1_a][i] == 2)
		return(1);  // temporarily unavailable
	    else if(screen_matrix[5*node_1_a][i] == -1)
		return(2);  // unavailable
        }
    }

    else if((node_2_b - node_1_b) == -1)
    {
	for(i=node_2_b+1; i<node_2_b+5; i++)
        {
	    if(screen_matrix[5*node_1_a][i] == 2)
		return(1);  // temporarily unavailable
	    else if(screen_matrix[5*node_1_a][i] == -1)
		return(2);  // unavailable
        }
    }

    return(0);  // the edge is available !    
}

/*
void state_robot(int msgqueue_id, int robot_id, int *segptr, int semid)  
{  
    mymsgbuf qbuf;  // modification of struct
    /* 
    typedef struct mymsgbuf
    {
    long mtype; / type 1: order, 2: break, 3. repair
    int robot_number;
    int a; 
    int b;
    }mymsgbuf;


    while(readshm(segptr, robot_id, 0) == 0)  //  While not stopped
    {  
	read_message(msgqueue_id, &qbuf, (phil_id+1));  // 
        printf("(Philosopher %d) Taking left fork\n", (phil_id+1));  
        fflush(stdout);  
   
    }  
    unlocksem(semid, 0);  
} 
*/

void show_screen(int **screen, int lane_x, int lane_y) 
{
    while(1)
    {
        print_screen_matrix(screen, lane_x, lane_y);

	printf("Enter your command: \n");
        printf("1. Give an order\n");
        printf("2. Break a robot\n");
        printf("3. Repair a robot\n"); 
	printf("0. Exit\n");
        printf("Your answer: ");
        scanf("%d", &response); 
    
        switch(response)
        {
	    case 1: 
            {
                printf("\033[H\033[J");
      	        print_screen_matrix(screen, lane_x, lane_y);
		printf("Which robot? ");
                scanf("%d", &robot_nbr);
		printf("Enter your x coordinates: ");
                scanf("%d", &coord_x);
		printf("Enter your y coordinates: ");
                scanf("%d", &coord_y);
		printf("Command received\n");
		sleep(0.5);
		break;
	    }
	    case 2: 
            {
                printf("\033[H\033[J");
      	        print_screen_matrix(screen, lane_x, lane_y);
		printf("Which robot? ");
                scanf("%d", &robot_nbr);
		printf("Command received\n");
		sleep(0.5);
		break;
	    }
            case 3:
            {
                printf("\033[H\033[J");
      	        print_screen_matrix(screen, lane_x, lane_y);
		printf("Which robot? ");
                scanf("%d", &robot_nbr);
		printf("Command received\n");
		sleep(0.5);
		break;
	    }
	}
	if(!response) 
        {
	    printf("\033[H\033[J");
            break;
        }
        printf("\033[H\033[J");
    } 
}


