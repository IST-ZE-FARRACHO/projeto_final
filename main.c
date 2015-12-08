/******************************************************************************
 *
 * File Name: main.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		Main program
 *
 *****************************************************************************/

#include "includes.h"

int main(int argc, char *argv[])
{	
	int restrictsActivator = NO_RESTRICTS;

	Park * park;
	Parking_spot **spots_matrix;

	LinkedList * carlist, * wait_carlist, * restrictionlist; /*Declares list*/

	park = ReadFilePark(argv[1]); /*Reads, allocates, and fills park matrix*/

	carlist = initLinkedList();
	wait_carlist = initLinkedList();
	restrictionlist = initLinkedList();

	if(argc > 3) /*if there's a restrictions file*/
	{
		restrictionlist = ReadRestrictsFile(argv[3], restrictionlist); /*Sends list pointer to function*/
		restrictsActivator = ACTIVE_RESTRICTS;
	}

	int st[park->G->V]; /*parents vector*/
	long int wt[park->G->V]; /*weight vector*/

	spots_matrix = CreatesSpotsTable(park);  /*creates matrix*/

	InsertSpotMatrix(park, spots_matrix, st, wt); /*inserts each spot for each access ordered by distance*/

	ReadMoveCars(park, argv[2], spots_matrix, carlist, wait_carlist, st, wt, restrictionlist, restrictsActivator);

	


	FreePark(park);

		exit(0);
}