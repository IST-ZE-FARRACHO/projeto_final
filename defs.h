/******************************************************************************
 *
 * File Name: defs.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 #ifndef defs_H
 #define defs_H

 #define NAME_SIZE 4

typedef void * Item;

struct _position
{
	int x;
	int y;
	int z;
};

typedef struct _position Position;

/********************************************************/
struct _node
{
	Position * pos;
	int type;
	int status;
};

typedef struct _node Graph_node;
/**************************************************************************/

struct _entrance 
{ /*struct for entrances*/
	char name[NAME_SIZE]; /*name of the entrance*/
	Position * pos;
};

typedef struct _entrance Entrance;

/*********************************************************************/
struct _access
{
	char name[NAME_SIZE]; /*name of the access*/
	char type;
 	Position * pos;
};

typedef struct _access Access;

/***************************************************************************/
struct _car /*Struct for cars*/
{
	char *id; /*Vehicle identification*/
	int ta; /*Car event time*/
	char type; /*Type of access required //“C” (Cinema), “H” (Habitacão), “E” (Escritorios), “L” (Loja) ou “R”(Restauracao)*/
	char inout; /*'E' for entrance event, 'S' for exit event*/

	Position * pos;

};

typedef struct _car Car;

/****************************************************************************/
struct _restFloor
{
	int ta;
	int tb;
	int px;
};

typedef struct _restFloor Rest_floor;

/********************************************************************************/
struct _restPos
{
	int ta;
	int type;
	int tb;
	Position * pos;
};

typedef struct _restPos Rest_pos;

/*******************************************************************************/
struct _restrict
{
	int type; /*0 - Position Restriction | 1 - Floor Restriction*/
	int ta; /*Occurence time*/
	char inout; /*'O' for restriction creation, 'F' for restriction lift*/
	Position * pos;
};

typedef struct _restrict Restrictions;

/*************************************************************************************/

/*
 *  Data Type: LinkedListStruct
 *
 *  Description: Structure with:
 *                 1) Pointer to the item of the linked list node
 *                 2) Pointer to next node of the linked list.
 */

/*
 *  Data type: LinkedList
 *
 *  Description: Node of a linked list
 */
typedef struct LinkedListStruct LinkedList;
struct LinkedListStruct
{
  Item this;
  LinkedList * next;
};


/************************************************************************/
typedef struct node link;

struct node
{
	int v;
	int weight; /*type of the node*/
	link *next;
};

/**************************************************************************/
struct graph 
{
	long int V; /*number of nodes*/
	long int E; /*number of edges*/
	link **adj;
	Graph_node *node_info; /*vector with the info about each node*/
};

typedef struct graph Graph;

/************************************************************************/
struct edge
{
	long int v; /*node 1*/
	long int w; /*node 2*/
	int weight;
};

typedef struct edge Edge;

/**********************************************************/
struct _spot
{
	long int node;
	long int distance;
	int status;
};

typedef struct _spot Parking_spot;

/************************************************************************/
struct _park 
{
 	int N; /*number of columns*/
 	int M; /*number of lines*/
 	int P; /*number of floors*/
 	int E; /*number of entrances*/
 	int S; /*number of accesses*/
 	int Spots; /*number of parking spots*/
 	Graph *G;
 	Entrance *entries; /*vector that stores the info about the entrances*/
 	Access *accesses; /*vector that stores the info about the accesses*/
};

typedef struct _park Park;
/*************************************************************************/

struct _heap 
{
  int (*less) (Item, Item);     /* Surprise! this field is a function pointer*/
                                /* to elements in the heap. */
  void (*print) (Item);         /* So is this one!! */
  int n_elements;               /* # elements in heap */
  int size;                     /* max size of the heap. */
  Item *heapdata;               /* An array of Items. */
};

typedef struct _heap Heap; 
/***************************************************/

void (*PrintItem) (Item);


 #endif