#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
//#define BIG_EXAMPLE
 
typedef struct node_t node_t, *heap_t;
typedef struct edge_t edge_t;
struct edge_t {
	node_t *nd;	/* target of this edge */
	edge_t *sibling;/* for singly linked list */
	int len;	/* edge cost */
};
struct node_t {
	edge_t *edge;	/* singly linked list of edges */
	node_t *via;	/* where previous node is in shortest path */
	double dist;	/* distance from origining node */
	char name[8];	/* the, er, name */
	int heap_idx;	/* link to heap position for updating distance */
};

typedef struct Path Path;
struct Path{
	int *arr;
	int size;
	int maxSize;
};
 
/* --- edge management --- */
void free_edges();
 
/* Don't mind the memory management stuff, they are besides the point.
   Pretend e_next = malloc(sizeof(edge_t)) */
void add_edge(node_t *a, node_t *b, double d);
 

/* --- priority queue stuff --- */
 
void set_dist(node_t *nd, node_t *via, double d);
 
node_t * pop_queue();
 
/* --- Dijkstra stuff; unreachable nodes will never make into the queue --- */
void calc_all(node_t *start);
 
void show_path(node_t *nd, Path *path);

void dijkstra(int **matrix, int size, int start, int end, Path *path);
