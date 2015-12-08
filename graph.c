/******************************************************************************
 *
 * File Name: graph.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		creates graph
 *
 *****************************************************************************/

#include "includes.h"

 #define P (wt[v] + t->weight)

/******************************************************************************
 * NEW()
 *
 * Arguments: v
 *             next - next node of list
 * Returns: link struct
 * Description: Creates a new node of the linked struct
 *
 *****************************************************************************/
link * NEW(int v, int weight, link *next)
{
	link * x = (link *) malloc(sizeof(link));

	if (x == NULL)
	{
		exit(0);
	}

	x->v = v;
	x->weight = weight;
	x->next = next;

	return x;
}

/******************************************************************************
 * EDGE()
 *
 * Arguments: v - node 1
 *            w - node 2
 *            weight
 * Returns: Edge
 * Description: Creates an edge
 *
 *****************************************************************************/

Edge * EDGE(int v, int w, int weight)
{
	Edge * e;
	e = (Edge *) malloc(sizeof(Edge));

	if(e == NULL)
	{
		exit(0);
	}

	e->v = v;
	e->w = w;
	e->weight = weight;

	return e;
}

/******************************************************************************
 * GRAPHinit()
 *
 * Arguments: V - number of nodes

 * Returns: Graph
 * Description: Creates a graph with the final number of nodes, but with no edges
 *
 *****************************************************************************/

Graph *GRAPHinit(long int V)
{
	long int i;
	Graph *G = (Graph *) malloc(sizeof(struct graph));

	if(G == NULL)
	{
		exit(0);
	}

	G->V = V;
	G->E = 0;
	G->adj = (link **) malloc(V * sizeof(link *));
	G->node_info = (Graph_node *) malloc(V * sizeof(Graph_node));

	if(G->adj == NULL || G->node_info == NULL)
	{
		exit(0);
	}

	for(i = 0; i < V; i++)
	{
		G->node_info[i].pos = (Position *) malloc(sizeof(Position));

		if(G->node_info[i].pos == NULL)
		{
			exit(0);
		}
	} 

	for (i = 0; i < V; i++)
		G->adj[i] = NULL;

	return G;
}

/******************************************************************************
 * GRAPHinsertE()
 *
 * Arguments: G - graph
 			  e - struct of edges
 *            value - edge weight
 *
 * Description: Inserts a new edge, if it doesn't exist
 *
 *****************************************************************************/

 void GRAPHinsertE(Graph *G, Edge *e) 
 {
 	long int v = e->v, w = e->w, weight = e->weight;

 	G->adj[v] = NEW(w, weight, G->adj[v]);
 	G->adj[w] = NEW(v, weight, G->adj[w]);

 	free(e);

 	G->E++;
 }

 /******************************************************************************
 * GRAPHremoveE()
 *
 * Arguments: G - graph
 *            e - struct of edges
 * Description: Removes an edge from the graph, if the edge exists
 *
 *****************************************************************************/

 void GRAPHremoveE(Graph *G, Edge *e)
 {
 	int v = e->v, w = e->w;

 	link * temp;
 	link * head;

 	head = G->adj[v];

 	for(temp = G->adj[v]->next; temp->v != w; temp = temp->next)
 	{
 		head = head->next;
 	}

 	head->next = temp->next;
 	free(temp);

 	link * temp2;

 	head = G->adj[w];

 	for(temp2 = G->adj[v]->next; temp2->v != v; temp2 = temp2->next)
 	{
 		head = head->next;
 	}

 	head->next = temp2->next;
 	free(temp2);

 	G->E--;
 }

 /******************************************************************************
 * GRAPdestroy()
 *
 * Arguments: G - graph
 *
 * Description: Deletes a graph
 *
 *****************************************************************************/

 void GRAPHdestroy(Graph *G)
 {
 	int i;
 	link * head;
 	link * aux;

 	for(i = 0; i < G->V; i++)
 	{
 		for(head = G->adj[i]; head != NULL; )
 		{
 			aux = head;
 			head = head->next;
 			free(aux);
 		}
 	}

 	for(i = 0; i < G->V; i++)
	{
		free(G->node_info[i].pos);

	} 
	
	free(G->node_info);
 	free(G->adj);	
 	free(G);
 }

 /******************************************************************************
 * LessNumPQ()
 *
 * Arguments: Item a, b
 *
 * Description: Compares two numbers
 *
 *****************************************************************************/

int LessNumPQ (Item a, Item b)
{
  int aa, bb;

  aa = (long int) a;
  bb = (long int) b;
  return (aa < bb);
}

 /******************************************************************************
 * GRAPHpfs()
 *
 * Arguments: G - graph
 *	          s
 *
 * Description: Dijkstra's Algorithm
 *
 *****************************************************************************/

void GRAPHpfs(Graph *G, long int s, int st[], long int wt[], int passTroughSpot)
 {
 	long int w, count = 0, min = INFINITE;
 	int adj = 0;
 	link * t;
 	long int v, i;
 	double maxWT = INFINITE;

 	Heap * queue;

 	queue = NewHeap(G->V, LessNumPQ);

 	for(v = 0; v < G->V; v++)
 	{
 		st[v] = -1;
 		wt[v] = maxWT;
    	Insert(queue, (Item) v);
 	}

 	wt[s] = 0.0;
 	FixDownPQ(queue, s, wt);

 	if(passTroughSpot == 1)
 		for(t = G->adj[s]; t != NULL; t = t->next) /*counts the adjacents of the spot*/
 			adj++;

 	for(i = 0; i < G->V; i++)
 		while(HeapEmpty(queue) != 1){
 			v = RemoveMin(queue, wt);

 			if(v <= min)
 				min = v;

 			if(wt[v] != maxWT)
 			{
 				for(t = G->adj[v]; t != NULL; t = t->next){
 					if(passTroughSpot == 1 && count < adj)
 					{
  						if(wt[w = t->v])
 						{
 							wt[w] = P;
 							FixDownPQ(queue, w, wt);
 							st[w] = v;
 						}	
 						count++;					
 					}
 					else if(wt[w = t->v] > P  && G->node_info[v].type != EMPTY_SPOT && G->node_info[v].status != CANT_GO)
 					{
 						wt[w] = P;
 						FixDownPQ(queue, w, wt);
 						st[w] = v;
 					}
 				}
 			}
 		}
 }