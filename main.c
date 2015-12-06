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
	Park * park;
	Parking_spot **spots_matrix;

	LinkedList * carlist, * wait_carlist, * restrictionlist; /*Declares list*/

	park = ReadFilePark(argv[1]); /*Reads, allocates, and fills park matrix*/

	carlist = initLinkedList();
	wait_carlist = initLinkedList();
	restrictionlist = initLinkedList();

	restrictionlist = ReadRestrictsFile(argv[3], restrictionlist); /*Sends list pointer to function*/

	int st[park->G->V];
	long int wt[park->G->V];

	spots_matrix = CreatesSpotsTable(park);

	InsertSpotMatrix(park, spots_matrix, st, wt);

	printf("\n\n");

	/*for(i = 0; i < park->S; i++)
	{
		for(j = 0; j < park->Spots; j++)
		{
			printf("%d  ", spots_matrix[i][j].node);
		}
		printf("\n\n");
	}*/

	ReadMoveCars(park, argv[2], spots_matrix, carlist, wait_carlist, st, wt);


	/*Mudanças de direção
		Nó 138
		Estacionamentos mal
		Aplicar restrições ----- QUASE CHECK CARALHOOOOO
		SAÍDA DE CARROS  ----DEVE ESTAR TAMBÉM
		LIsta de espera
		FICHEIRO GRANDE DÁ SEG FAULT*/


	/*update das restrições
	  ler um carro
		se for entrada, adiciona à lista de carros,
			cria um caminho da entrada até ao spot mais perto do acesso pretendido
				cria um caminho do spot até ao acesso
					escreve no ficheiro de saida
		se for saída
			procura na lista de carros pelo carro
				liberta a posição do carro no grafo
					apaga o nodo da lista
					*/

		exit(0);
}