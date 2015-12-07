/******************************************************************************
 *
 * File Name: cars.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION: Reads info about car entrance/exit/unparking
 *
 *****************************************************************************/

#include "includes.h"

/******************************************************************************
 * NewCar()
 *
 * Arguments: Car info
 *
 * Returns: Pointer to created Car
 *
 * Description: Allocates a new Car structure
 *
 *****************************************************************************/

Car * NewCar(char * id, int ta, char type, char inout, int xs, int ys, int zs)
{
	Car * newcar;

	newcar = (Car *) malloc(sizeof(Car));
	if (newcar == NULL) 
	{
		fprintf(stderr, "Error in malloc of new car.\n");
		exit(0);
	}

	newcar->id = (char *) malloc(sizeof(char)*(strlen(id) + 1));
	if (newcar->id == NULL) 
	{
		fprintf(stderr, "Error in malloc of new car id.\n");
		exit(0);
	}

	newcar->pos = (Position*) malloc(sizeof(Position));

 	if(newcar->pos == NULL)
 	{
 		fprintf(stderr, "Error in malloc of entries/accesses.\n");
 		exit(0);
 	}


	strcpy(newcar->id, id);
	newcar->ta = ta;
	newcar->type = type;
	newcar->inout = inout;
	newcar->pos->x = xs;
	newcar->pos->y = ys;
	newcar->pos->z = zs;

	return (newcar);
}

void DeleteCarFromList(LinkedList * list, Car * target, int * x, int * y, int * z)
{
	int counter = 0;
	Car * searchcar;
	LinkedList * aux = list, * prev = aux;

 	for(aux = list; aux != NULL; aux = aux->next) /* Searches carlist */
 	{
 		searchcar = (Car *) getItemLinkedList(aux); /* Gets it from the abstract structure */
		(*x) = searchcar->pos->x;
		(*y) = searchcar->pos->y;
		(*z) = searchcar->pos->z;

		if(strcmp(searchcar->id, target->id) == 0) /* If it matches the ID */
 		{
 			if(counter == 0) /*its in the head of the list*/
 			{
 				list = aux->next;
 				free(aux);
 				break;
 			}	
 			else
 			{
				prev->next = aux->next;
				free(aux);
				break; 							
 			}
 		}
 		else
 		{
 			prev = aux;
 		}
 		counter++;
 	}	
}


void WriteParkPath(FILE *fp, Park * p, Car * new, Parking_spot ** spots_matrix, LinkedList * carlist, LinkedList * wait_carlist, int st[], long int wt[])
{
	int writeOut, y, x, destinedSpot, destinedAccess, distance = p->G->V, actualPos, prevPos, prevprevPos, i = 0, j = 1, parent, gotSpot = 0;
	int pX, pY, pZ, origin, totaltime = new->ta, xspot, yspot, count = 0, parkedtime, totalweight;
	char tm;

	origin = Get_Pos(new->pos->x, new->pos->y, new->pos->z, p->N, p->M);

	GRAPHpfs(p->G, origin, st, wt, 0);

	/*get parking spot*/
	for(y = 0; y < p->S; y++)
	{
		if(p->accesses[y].type == new->type)
		{
			for(x = 0; x < p->Spots; x++)
			{
				if(spots_matrix[y][x].status == CAN_GO)
				{
					if(spots_matrix[y][x].distance < distance)
					{
						destinedSpot = spots_matrix[y][x].node;
						distance = spots_matrix[y][x].distance;
						xspot = x;
						yspot = y;
						destinedAccess = Get_Pos(p->accesses[y].pos->x, p->accesses[y].pos->y, p->accesses[y].pos->z, p->N, p->M);
printf("%d\n\n", destinedSpot);
						gotSpot = 1;
					}
				}
			}
		}
	}
	if(gotSpot == 0) /*if the park is totally occupied*/
	{
		wait_carlist = insertSortedLinkedList(wait_carlist, (Item) new, LessNumCar);
	}

	else
	{
		carlist = insertUnsortedLinkedList(carlist, (Item) new); /*Inserts new car in given car list*/
		/*get path*/

		/*for(i = 0; i < p->G->V; i++)
			printf("Parent: %d  Distance: %ld   Node: %d   Coord: %d %d %d\n", st[i], wt[i], i, p->G->node_info[i].pos->x, p->G->node_info[i].pos->y, p->G->node_info[i].pos->z);
*/
		int carPathBackwards[wt	[destinedSpot]];

		carPathBackwards[i] = parent = destinedSpot;

		while(parent != origin)
		{
			i++;
			carPathBackwards[i] = st[parent];
			parent = st[parent];
		}

		/*write entrance*/
		tm = 'i';

		writeOut = escreve_saida(fp, new->id, totaltime, new->pos->x, new->pos->y, new->pos->z, tm);

		if(writeOut == -1)
			exit(0);

		/*write movement*/
		totaltime++;
		prevPos = prevprevPos = origin;
		actualPos = carPathBackwards[--i];
		tm = 'm';

		while(actualPos != destinedSpot)
		{
			new->pos->x = p->G->node_info[actualPos].pos->x;
			new->pos->y = p->G->node_info[actualPos].pos->y;
			new->pos->z = p->G->node_info[actualPos].pos->z;
			
			if(j < 2)
				writeOut = escreve_saida(fp, new->id, totaltime, new->pos->x, new->pos->y, new->pos->z, tm);
			
			else
			{
				if((new->pos->x != p->G->node_info[prevprevPos].pos->x && new->pos->y != p->G->node_info[prevprevPos].pos->y) || (new->pos->z != p->G->node_info[prevprevPos].pos->z))
				{
					if(count == 0){
						writeOut = escreve_saida(fp, new->id, totaltime - 1,  p->G->node_info[prevPos].pos->x,  p->G->node_info[prevPos].pos->y,  p->G->node_info[prevPos].pos->z, tm);
						count = 1;
					}
					writeOut = escreve_saida(fp, new->id, totaltime, new->pos->x, new->pos->y, new->pos->z, tm);
				}
				else
					count = 0;
			}

			prevprevPos = prevPos;
			prevPos = actualPos;
			actualPos = carPathBackwards[--i];
			totaltime++;
			j++;
		}

		/*write parking*/
		tm = 'e';
		pX = p->G->node_info[actualPos].pos->x;
		pY = p->G->node_info[actualPos].pos->y,
		pZ = p->G->node_info[actualPos].pos->z;
		parkedtime = totaltime;
		totalweight = wt[actualPos];

		if(count == 0)
			writeOut = escreve_saida(fp, new->id, totaltime - 1,  p->G->node_info[prevPos].pos->x,  p->G->node_info[prevPos].pos->y,  p->G->node_info[prevPos].pos->z, 'm');
		writeOut = escreve_saida(fp, new->id, totaltime,pX, pY, pZ, tm);

		spots_matrix[yspot][xspot].status = CANT_GO;

		GRAPHpfs(p->G, actualPos, st, wt, 1);
	
		i = 0, j = 0, count = 0;
		int PedPathBackwards[wt[destinedAccess]];
		PedPathBackwards[i] = parent = destinedAccess;
	
		do
		{
			i++;
			PedPathBackwards[i] = st[parent];
			parent = st[parent];		
		}
		while(parent != destinedSpot);

		prevPos = prevprevPos = destinedSpot;
		actualPos = PedPathBackwards[--i];
		tm = 'p';
		totaltime++;

		while(actualPos != destinedAccess)
		{
			pX = p->G->node_info[actualPos].pos->x;
			pY = p->G->node_info[actualPos].pos->y;
			pZ = p->G->node_info[actualPos].pos->z;
printf("%d %d\n\n", actualPos, destinedAccess);
			if(j < 2)
				writeOut = escreve_saida(fp, new->id, totaltime, pX, pY, pZ, tm);
			
			else
			{
				if((pX != p->G->node_info[prevprevPos].pos->x && pY != p->G->node_info[prevprevPos].pos->y) || (pZ != p->G->node_info[prevprevPos].pos->z))
				{
					if(count == 0)
					{
						writeOut = escreve_saida(fp, new->id, totaltime - 1,  p->G->node_info[prevPos].pos->x,  p->G->node_info[prevPos].pos->y,  p->G->node_info[prevPos].pos->z, tm);
						count = 1;
					}
					writeOut = escreve_saida(fp, new->id, totaltime, new->pos->x, new->pos->y, new->pos->z, tm);
				}
				else
					count = 0;
			}
	
			prevprevPos = prevPos;
			prevPos = actualPos;
			actualPos = PedPathBackwards[--i];
			totaltime++;
			j++;
		}
	
		tm = 'x';
		pX = p->G->node_info[actualPos].pos->x;
		pY = p->G->node_info[actualPos].pos->y;
		pZ = p->G->node_info[actualPos].pos->z;
		totalweight += wt[actualPos];

		if(count == 0)
			writeOut = escreve_saida(fp, new->id, totaltime - 1,  p->G->node_info[prevPos].pos->x,  p->G->node_info[prevPos].pos->y,  p->G->node_info[prevPos].pos->z, 'm');
			fprintf(fp, "%s %d %d %d %d x", new->id, new->ta, parkedtime, totaltime, totalweight);
	}
}


/******************************************************************************
 * ReadCarFile()
 *
 * Arguments: Park
 *			  Car file
 *			  Car list
 *			  Liberation list
 *
 * Returns: Updated car list and liberation list
 *
 * Description: Reads car file and stores info into a list
 *
 *****************************************************************************/
void ReadMoveCars(Park * p, char * file, Parking_spot ** spots_matrix, LinkedList * carlist, LinkedList * wait_carlist, int st[], long int wt[], LinkedList * restrictionlist, int RestrictActivator)
{

	 FILE *f; 
	 FILE *output;

	 int n, tmpta, tmpxs, tmpys, tmpzs, leavePos, y, x, xpos = 0, ypos = 0, zpos = 0;
	 char tmptype;
	 char tmpid[5];
	 char * fileNameOut = GetOutputName(file);
	 Car * newc, * search;
	 LinkedList * aux;

 	f = AbreFicheiro(file, "r"); /* Opens input file */
 	output = AbreFicheiro(fileNameOut, "w"); /* Opens output file */

 	do{	
 		for(aux = carlist; aux != NULL; aux = aux->next){
 			search = getItemLinkedList(aux);
 			printf("%s  ", search->id);
 		}
 		printf("%d\n\n", lengthLinkedList(carlist));
 		n = fscanf(f, "%s %d %c %d %d %d", tmpid, &tmpta, &tmptype, &tmpxs, &tmpys, &tmpzs); /* Reads each line*/
 		if( n < 3 ) continue;

 		if(tmptype != 'S') /*If it is not exit info (it is an entrance)*/
 		{	
			newc = NewCar(tmpid, tmpta, tmptype, 'E', tmpxs, tmpys, tmpzs); /*Creates new car*/
			if(RestrictActivator == ACTIVE_RESTRICTS)
				UpdateRestrictions(restrictionlist, p, newc, spots_matrix);
 			WriteParkPath(output, p, newc, spots_matrix, carlist, wait_carlist, st, wt); /* Writes on the output file*/
 		}

 		else
 		{
 			if(n > 3) /* If it is a spot liberation*/
 			{
 				leavePos = Get_Pos(tmpxs, tmpys, tmpzs, p->N, p->M); /* Gets the leaving position */
 				p->G->node_info[leavePos].status = CAN_GO; /* Lifts block */
 				p->G->node_info[leavePos].type = EMPTY_SPOT; /* It is now an empty spot */

 				for(y = 0; y < p->S; y++)
					for(x = 0; x < p->Spots; x++)
						if(leavePos == spots_matrix[y][x].node)
							spots_matrix[y][x].status = CAN_GO; /* Updates spots matrix */
 			}
 
 			if(n == 3) /*Exit case - Car is in carlist, register exit time*/
 			{
 				DeleteCarFromList(carlist, newc, &xpos, &ypos, &zpos);

 				leavePos = Get_Pos(xpos, ypos, zpos, p->N, p->M);

 				for(y = 0; y < p->S; y++)
					for(x = 0; x < p->Spots; x++)
						if(leavePos == spots_matrix[y][x].node)
						{
							spots_matrix[y][x].status = CAN_GO; /* Updates spots matrix */
							p->G->node_info[leavePos].status = CAN_GO; /* Updates graph info */
						}
 			}

 			if(lengthLinkedList(wait_carlist) > 0)
 			{
 				newc = (Car *) getItemLinkedList(wait_carlist);
 				if(RestrictActivator == ACTIVE_RESTRICTS)
					UpdateRestrictions(restrictionlist, p, newc, spots_matrix);
 			
 				DeleteCarFromList(wait_carlist, newc, &xpos, &ypos, &zpos);

 				WriteParkPath(output, p, newc, spots_matrix, carlist, wait_carlist, st, wt); /* Writes on the output file*/			
 			}

 		}
 	}
 	while(n >= 3);

 	FechaFicheiro(f);
 	FechaFicheiro(output);
}