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
		exit(0);
	}

	newcar->id = (char *) malloc(sizeof(char)*(strlen(id) + 1));
	if (newcar->id == NULL) 
	{
		exit(0);
	}

	newcar->pos = (Position*) malloc(sizeof(Position));

 	if(newcar->pos == NULL)
 	{
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

/******************************************************************************
 * DeleteCarFromList()
 *
 * Arguments: list
 *            name of the car
 *            x, y, z - coordenates for the position of the car
 *			 
 * Returns: --
 *
 * Description: Deletes a car from either the wait_carlist or the carlist
 *
 *****************************************************************************/

LinkedList * DeleteCarFromList(LinkedList * list, char *id, int * x, int * y, int * z)
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

		if(strcmp(searchcar->id, id) == 0) /* If it matches the ID */
 		{
			(*x) = searchcar->pos->x;
			(*y) = searchcar->pos->y;
			(*z) = searchcar->pos->z;

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

 	return list;
}

/******************************************************************************
 * WriteParkPath()
 *
 * Arguments: file
 *            park
 *            car to write
 *            spots matrix
 *            wait_carlist, carlist
 *            parent and weight vectors
 *			 
 * Returns: 
 *
 * Description: Writes the car movements on the output file
 *
 *****************************************************************************/

void WriteParkPath(FILE *fp, Park * p, Car * new, Parking_spot ** spots_matrix, LinkedList ** carlist, LinkedList * wait_carlist, int st[], long int wt[], int timeWaitList)
{
	int writeOut, y, x, destinedSpot = 0, destinedAccess = 0, distance = INFINITE, actualPos, prevPos, prevprevPos, i = 0, parent, gotSpot = 0;
	int pX, pY, pZ, origin, totaltime = new->ta, xspot = 0, yspot = 0, parkedtime, totalweight;
	char tm;

	origin = Get_Pos(new->pos->x, new->pos->y, new->pos->z, p->N, p->M);

	GRAPHpfs(p->G, origin, st, wt, 0);

	/* Get best parking spot */

	for(y = 0; y < p->S; y++) /* For each one of the accesses */
	{
		if(p->accesses[y].type == new->type) /* If the access matches the new car wanted access */
		{
			for(x = 0; x < p->Spots; x++) /* For each one of the spots in the park */
			{
				if(spots_matrix[y][x].status == CAN_GO) /* If the spot has a CAN_GO status */
				{
					if(spots_matrix[y][x].distance < distance) /* Saves minimum distance */
					{
						destinedSpot = spots_matrix[y][x].node; /* That is the node we want to reach */
						distance = spots_matrix[y][x].distance; /* New distance is the new minimum distance */
						xspot = x;
						yspot = y;
						destinedAccess = Get_Pos(p->accesses[y].pos->x, p->accesses[y].pos->y, p->accesses[y].pos->z, p->N, p->M);

						gotSpot = 1;
					}
				}
			}
		}
	}

	if(gotSpot == 0) /*if the park is totally occupied*/
	{	
		wait_carlist = insertSortedLinkedList(wait_carlist, (Item) new, LessNumCar);
		return;
	}

	else
	{	
		/*get path*/
		int carPathBackwards[wt[destinedSpot]];
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
			
			if((new->pos->x != p->G->node_info[prevprevPos].pos->x && new->pos->y != p->G->node_info[prevprevPos].pos->y) || (new->pos->z != p->G->node_info[prevprevPos].pos->z))
			{
				writeOut = escreve_saida(fp, new->id, totaltime - 1,  p->G->node_info[prevPos].pos->x,  p->G->node_info[prevPos].pos->y,  p->G->node_info[prevPos].pos->z, tm);
			}

			prevprevPos = prevPos;
			prevPos = actualPos;
			actualPos = carPathBackwards[--i];

			totaltime++;
		}

		/*write parking*/
		tm = 'e';
		pX = new->pos->x = p->G->node_info[destinedSpot].pos->x;
		pY = new->pos->y = p->G->node_info[destinedSpot].pos->y;
		pZ = new->pos->z = p->G->node_info[destinedSpot].pos->z;
		parkedtime = totaltime;
		totalweight = wt[actualPos];

		*carlist = insertUnsortedLinkedList(*carlist, (Item) new); /*Inserts new car in given car list*/

		if((pX != p->G->node_info[prevprevPos].pos->x && pY != p->G->node_info[prevprevPos].pos->y) || (pZ != p->G->node_info[prevprevPos].pos->z))
		{
			writeOut = escreve_saida(fp, new->id, totaltime - 1,  p->G->node_info[prevPos].pos->x,  p->G->node_info[prevPos].pos->y,  p->G->node_info[prevPos].pos->z, 'm');
		}
		
		writeOut = escreve_saida(fp, new->id, totaltime,pX, pY, pZ, tm);

		spots_matrix[yspot][xspot].status = CANT_GO;

		GRAPHpfs(p->G, actualPos, st, wt, 1);


		i = 0;
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

			if((pX != p->G->node_info[prevprevPos].pos->x && pY != p->G->node_info[prevprevPos].pos->y) || (pZ != p->G->node_info[prevprevPos].pos->z))
			{
				writeOut = escreve_saida(fp, new->id, totaltime - 1,  p->G->node_info[prevPos].pos->x,  p->G->node_info[prevPos].pos->y,  p->G->node_info[prevPos].pos->z, tm);
			}
	
			prevprevPos = prevPos;
			prevPos = actualPos;
			actualPos = PedPathBackwards[--i];

			totaltime++;
		}

		tm = 'a';
		pX = p->G->node_info[actualPos].pos->x;
		pY = p->G->node_info[actualPos].pos->y;
		pZ = p->G->node_info[actualPos].pos->z;
		totalweight += 3*wt[actualPos];

		if((pX != p->G->node_info[prevprevPos].pos->x && pY != p->G->node_info[prevprevPos].pos->y) || (pZ != p->G->node_info[prevprevPos].pos->z))
		{
			writeOut = escreve_saida(fp, new->id, totaltime - 1,  p->G->node_info[prevPos].pos->x,  p->G->node_info[prevPos].pos->y,  p->G->node_info[prevPos].pos->z, 'p');
		}

		writeOut = escreve_saida(fp, new->id, totaltime, pX, pY, pZ, tm);

		totaltime += timeWaitList;

		fprintf(fp, "%s %d %d %d %d x\n", new->id, new->ta, parkedtime, totaltime, totalweight);
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
 * Description: Reads each car and performes the insertions/deletes on the wait_carlist, carlist
 *              Updates the restrictions
 *
 *****************************************************************************/
void ReadMoveCars(Park * p, char * file, Parking_spot ** spots_matrix, LinkedList * carlist, LinkedList * wait_carlist, int st[], long int wt[], LinkedList * restrictionlist, int RestrictActivator)
{

	 FILE *f; 
	 FILE *output;


	 int n, tmpta, tmpxs, tmpys, tmpzs, leavePos, y, x, xpos = 0, ypos = 0, zpos = 0, timeWaitList;

	 char tmptype;
	 char tmpid[5];
	 char * fileNameOut = GetOutputName(file);
	 Car * newc;

 	f = AbreFicheiro(file, "r"); /* Opens input file */

 	output = AbreFicheiro(fileNameOut, "w"); /* Opens output file */

 	do{	
 		timeWaitList = 0;

 		n = fscanf(f, "%s %d %c %d %d %d", tmpid, &tmpta, &tmptype, &tmpxs, &tmpys, &tmpzs); /* Reads each line*/

 		if( n < 3 ) continue;

 		if(tmptype != 'S') /*If it is not exit info (it is an entrance)*/
 		{	
			newc = NewCar(tmpid, tmpta, tmptype, 'E', tmpxs, tmpys, tmpzs); /*Creates new car*/
			if(RestrictActivator == ACTIVE_RESTRICTS)
				UpdateRestrictions(restrictionlist, p, newc, spots_matrix);

 			WriteParkPath(output, p, newc, spots_matrix, &carlist, wait_carlist, st, wt, timeWaitList); /* Writes on the output file*/
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
						{
							spots_matrix[y][x].status = CAN_GO; /* Updates spots matrix */
						}
				fprintf(output,"%s %d %d %d %d s\n", tmpid, tmpta, tmpxs, tmpys, tmpzs);
 			}
 
 			if(n == 3) /*Exit case - Car is in carlist, register exit time*/
 			{	


 				DeleteCarFromList(carlist, tmpid, &xpos, &ypos, &zpos);

 				leavePos = Get_Pos(xpos, ypos, zpos, p->N, p->M);
 
 				for(y = 0; y < p->S; y++)
					for(x = 0; x < p->Spots; x++)
						if(leavePos == spots_matrix[y][x].node)
						{
							spots_matrix[y][x].status = CAN_GO; /* Updates spots matrix */
							p->G->node_info[leavePos].status = CAN_GO; /* Updates graph info */
						}

				fprintf(output,"%s %d %d %d %d s\n", tmpid, tmpta, xpos, ypos, zpos);
 			}

 			if(lengthLinkedList(wait_carlist) > 0)
 			{	
 				newc = (Car *) getItemLinkedList(wait_carlist);
 				if(RestrictActivator == ACTIVE_RESTRICTS)
					UpdateRestrictions(restrictionlist, p, newc, spots_matrix);

				timeWaitList = tmpta - newc->ta;
				newc->ta = tmpta;
 				WriteParkPath(output, p, newc, spots_matrix, &carlist, wait_carlist, st, wt, timeWaitList); /* Writes on the output file*/	

				wait_carlist = DeleteCarFromList(wait_carlist, newc->id, &xpos, &ypos, &zpos);
 			}
 		}
 	}
 	while(n >= 3);

 	FechaFicheiro(f);
 	FechaFicheiro(output);
}