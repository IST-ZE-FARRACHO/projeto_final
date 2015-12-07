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
	int i, n;
	Park * park;
	Parking_spot **spots_matrix;
	LinkedList * aux;
	Restrictions * rest;

	LinkedList * carlist, * wait_carlist, * restrictionlist; /*Declares list*/

	park = ReadFilePark(argv[1]); /*Reads, allocates, and fills park matrix*/

	/*carlist = initLinkedList();
	wait_carlist = initLinkedList();
	restrictionlist = initLinkedList();

	restrictionlist = ReadRestrictsFile(argv[3], restrictionlist); /*Sends list pointer to function*/

	/*int st[park->G->V];
	long int wt[park->G->V];*/

	/*for(i = 0; i < park->G->V; i++)
		printf("Parent: %d  Distance: %ld   Node: %d   Coord: %d %d %d\n", st[i], wt[i], i, park->G->node_info[i].pos->x, park->G->node_info[i].pos->y, park->G->node_info[i].pos->z);
	*/
	/*spots_matrix = CreatesSpotsTable(park);

	InsertSpotMatrix(park, spots_matrix, st, wt);

	printf("\n\n");*/

	/*for(i = 0; i < park->S; i++)
	{
		for(j = 0; j < park->Spots; j++)
		{
			printf("%d  ", spots_matrix[i][j].node);
		}
		printf("\n\n");
	}*/

	/*ReadMoveCars(park, argv[2], spots_matrix, carlist, wait_carlist, st, wt, restrictionlist);*/

	FreePark(park);


	/*Mudanças de direção
		Nó 138
		Estacionamentos mal
		Aplicar restrições ----- QUASE CHECK CARALHOOOOO
		SAÍDA DE CARROS  ----DEVE ESTAR TAMBÉM
		LIsta de espera
		FICHEIRO GRANDE DÁ SEG FAULT*/

		exit(0);
}