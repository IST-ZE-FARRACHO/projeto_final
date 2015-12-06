/******************************************************************************
 *
 * File Name: restrictions.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		reads the file with the information about the restrictions
 *
 *****************************************************************************/

#include "includes.h"

/******************************************************************************
 * NewRestrictions ()
 *
 * Arguments: 
 * Returns: Restrictions
 *
 * Description: Creates a new Restrictions structure
 *
 *****************************************************************************/

Restrictions *NewRestrictions(int rest_type, int ta, char inout, int x, int y, int z)
{
	Restrictions * rest;

	rest = (Restrictions *) malloc(sizeof(Restrictions)); /*allocates memory for the struct*/

	if (rest == NULL)
	{
		fprintf(stderr, "Error in malloc of restrictions struct.\n");
		exit(0);
	}

	rest->pos = (Position*) malloc(sizeof(Position));

 	if(rest->pos == NULL)
 	{
 		fprintf(stderr, "Error in malloc of rest->pos.\n");
 		exit(0);
 	}


	rest->type = rest_type;
	rest->ta = ta;
	rest->inout = inout;
	rest->pos->x = x;
	rest->pos->y = y;
	rest->pos->z = z;

	return rest;
}

/******************************************************************************
 * ReadRestrictsFile ()
 *
 * Arguments: file
 * Returns: Restrictions
 *
 * Description: Reads the file with the restrictions
 *
 *****************************************************************************/
LinkedList * ReadRestrictsFile(char * file, LinkedList * restrictionslist)
{
	int ta, tb, ex, ey, ez, nr_reads;
	char r;
	Restrictions * aux;

	FILE * f;

	f = AbreFicheiro(file, "r");

	while((nr_reads = fscanf(f, "%s %d %d %d %d %d", &r, &ta, &tb, &ex, &ey, &ez))) /*Reads each line of the file*/
	{
		if(nr_reads == 4) /*Its a floor restriction - use type = 1*/
		{	
			aux = NewRestrictions(FLOOR, ta, 'E', DONTCARE, DONTCARE, ez);
			restrictionslist = insertUnsortedLinkedList(restrictionslist, (Item) aux); /*Inserts new floor restriction in restriction list*/
			aux = NewRestrictions(FLOOR, tb, 'S', DONTCARE, DONTCARE, ez);
			restrictionslist = insertUnsortedLinkedList(restrictionslist, (Item) aux); /*Inserts new floor restriction in restriction list*/

 		
		}
		else if(nr_reads == 6) /*Its a position restriction - use type = 0*/
		{
			aux = NewRestrictions(POSITION, ta, 'E', ex, ey, ez); /*Inserts restriction entrance time with ta and 'E'*/
			restrictionslist = insertUnsortedLinkedList(restrictionslist, (Item) aux); /*Inserts new position restriction in restriction list*/
			aux = NewRestrictions(POSITION, tb, 'S', ex, ey, ez); /*Inserts restriction lift time with tb and 'S'*/
			restrictionslist = insertUnsortedLinkedList(restrictionslist, (Item) aux); /*Inserts new position restriction in restriction list*/

		}

		else if(nr_reads != 4 || nr_reads != 6)
		{
			break;
		}
	}

	fclose(f);

	return restrictionslist;
}

void UpdateRestrictions(LinkedList * restrictionslist, Park * park, Car * new, Parking_spot ** spots_matrix)
{
	int i, nmbr, x, y;
	Restrictions * nextrestrict;
	LinkedList * aux;

	aux = restrictionslist;

	while(aux->next != NULL)
	{	
		nextrestrict = (Restrictions *) getItemLinkedList(aux);

		if(nextrestrict->ta > new->ta)
			return;

		if(nextrestrict->inout == 'E') /* New Restriction On */
		{
			if(nextrestrict->type == POSITIONREST) /* Position Restriction */
			{
				for(i = 0; i <= park->G->V; i++) /* For each one of the nodes */
				{	
					if( SamePos(park->G->node_info[i].pos, nextrestrict->pos) ) /* Update Graph status */
						park->G->node_info[i].status = CANT_GO;

					if( (park->G->node_info[i].type == EMPTY_SPOT) || (park->G->node_info[i].type == OCCUPIED) ) /* Update Matrix Spot status */
					{
						nmbr = Get_Pos(park->G->node_info[i].pos->x, park->G->node_info[i].pos->y, park->G->node_info[i].pos->z, park->N, park->M); /* Transforms coordinates into node number */
						
						for(y = 0; y < park->S; y++) /* For each one of the matrix columns (each one of the accesses) */
						{	
							for(x = 0; x < park->Spots; x++)
							{
								if(spots_matrix[y][x].node == nmbr) /* If it finds a Spot with the same coordinates */
									spots_matrix[y][x].status = CANT_GO; /* Blocks it */
							}
						}
					}

				}
			}
			else /* Floor Restriction */
			{
				for(y = 0; y < park->S; y++)
				{
					for(x = 0; x < park->Spots; x++)
					{
						if(park->G->node_info[spots_matrix[y][x].node].pos->z == nextrestrict->pos->z)
						{
							spots_matrix[y][x].status = CANT_GO;
							park->G->node_info[spots_matrix[y][x].node].status = CANT_GO;
						}

					}
				}	
			}
		}
		else /* Restriction OFF */
		{
			if(nextrestrict->type == POSITIONREST) /* Position Restriction */
			{

				for(i = 0; i <= park->G->V; i++) /*For each one of the nodes*/
				{	
					if( SamePos(park->G->node_info[i].pos, nextrestrict->pos) )
						park->G->node_info[i].status = CAN_GO;

						if( (park->G->node_info[i].type == EMPTY_SPOT) || (park->G->node_info[i].type == OCCUPIED) ) /* Update Matrix Spot status */
					{
						nmbr = Get_Pos(park->G->node_info[i].pos->x, park->G->node_info[i].pos->y, park->G->node_info[i].pos->z, park->N, park->M); /* Transforms coordinates into node number */
						
						for(y = 0; y < park->S; y++) /* For each one of the matrix columns (each one of the accesses) */
						{	
							for(x = 0; x < park->Spots; x++)
							{
								if(spots_matrix[y][x].node == nmbr) /* If it finds a Spot with the same coordinates */
									spots_matrix[y][x].status = CAN_GO; /* Allows it */
							}
						}
					}
				}
			}
			else /*Floor Restriction*/
			{

				for(y = 0; y < park->S; y++)
				{
					for(x = 0; x < park->Spots; x++)
					{
						if(park->G->node_info[spots_matrix[y][x].node].pos->z == nextrestrict->pos->z)
						{
							spots_matrix[y][x].status = CAN_GO;
							park->G->node_info[spots_matrix[y][x].node].status = CAN_GO;
						}

					}
				}
			}
		}
		aux = aux->next;
	}
}