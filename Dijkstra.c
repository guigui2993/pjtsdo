#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dijkstra.h"
 
/* --- edge management --- */
#ifdef BIG_EXAMPLE
#	define BLOCK_SIZE (1024 * 32 - 1)
#else
#	define BLOCK_SIZE 15
#endif
static edge_t *edge_root = 0, *e_next = 0;
 
/* Don't mind the memory management stuff, they are besides the point.
   Pretend e_next = malloc(sizeof(edge_t)) */
void add_edge(node_t *a, node_t *b, double d)
{
	if (e_next == edge_root) {
		edge_root = malloc(sizeof(edge_t) * (BLOCK_SIZE + 1));
		edge_root[BLOCK_SIZE].sibling = e_next;
		e_next = edge_root + BLOCK_SIZE;
	}
	--e_next;
 
	e_next->nd = b;
	e_next->len = d;
	e_next->sibling = a->edge;
	a->edge = e_next;
}
 
void free_edges()
{
	for (; edge_root; edge_root = e_next) {
		e_next = edge_root[BLOCK_SIZE].sibling;
		free(edge_root);
	}
}
 
/* --- priority queue stuff --- */
heap_t *heap;
int heap_len;
 
void set_dist(node_t *nd, node_t *via, double d)
{
	int i, j;
 
	/* already knew better path */
	if (nd->via && d >= nd->dist) return;
 
	/* find existing heap entry, or create a new one */
	nd->dist = d;
	nd->via = via;
 
	i = nd->heap_idx;
	if (!i) i = ++heap_len;
 
	/* upheap */
	for (; i > 1 && nd->dist < heap[j = i/2]->dist; i = j)
		(heap[i] = heap[j])->heap_idx = i;
 
	heap[i] = nd;
	nd->heap_idx = i;
}
 
node_t * pop_queue()
{
	node_t *nd, *tmp;
	int i, j;
 
	if (!heap_len) return 0;
 
	/* remove leading element, pull tail element there and downheap */
	nd = heap[1];
	tmp = heap[heap_len--];
 
	for (i = 1; i < heap_len && (j = i * 2) <= heap_len; i = j) {
		if (j < heap_len && heap[j]->dist > heap[j+1]->dist) j++;
 
		if (heap[j]->dist >= tmp->dist) break;
		(heap[i] = heap[j])->heap_idx = i;
	}
 
	heap[i] = tmp;
	tmp->heap_idx = i;
 
	return nd;
}
 
/* --- Dijkstra stuff; unreachable nodes will never make into the queue --- */
void calc_all(node_t *start)
{
	node_t *lead;
	edge_t *e;
 
	set_dist(start, start, 0);
	while ((lead = pop_queue()))
		for (e = lead->edge; e; e = e->sibling)
			set_dist(e->nd, lead, lead->dist + e->len);
}
 
void show_path(node_t *nd, Path* path)
{
	if (nd->via == nd)
		//printf("%s", nd->name);
		path->arr[path->size] = nd->name;
	else if (!nd->via)
		//printf("%s(unreached)", nd->name);
		path->size = -1;
	else {
		show_path(nd->via, path);
		path->arr[path->size++] = nd->name;
		//printf("-> %s(%g) ", nd->name, nd->dist);
	}
}

void dijkstra(int **matrix, int size, int start, int end, Path *path){
	int i, j;
 
	node_t *nodes = calloc(sizeof(node_t), size);
 
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if(matrix[i][j]){
				add_edge(nodes +i, nodes + j, 1);
				//add_edge(nodes[j], nodes[i], 1);
			}
		}
	}
 
	heap = calloc(sizeof(heap_t), size + 1);
	heap_len = 0;
 
	calc_all(nodes + start);

	int c = 0;
	node_t *nd = nodes + end;
	while(nd->via != nd){
		if(!nd->via){
			path->size = -1;
			return;
		}
		c++;
		nd = nd->via;
	}
	if(path->maxSize<c)
		path->arr = realloc(path->arr, c);

	path->size = 0;
	show_path(nodes + end, path);


	/* real programmers don't free memories (they use Fortran) */
	free_edges();
	free(heap);
	free(nodes);

	return 1;
}
