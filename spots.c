/******************************************************************************
 *
 * File Name: spots.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		reads the graph and creates the spots trees
 *
 *****************************************************************************/

#define EMPTY_SPOT 4
#define OCCUPIED 5

#include "includes.h"

 /******************************************************************************
 * quicksort()
 *
 * Arguments: spots matrix
 *            number of spots
 *			 
 * Returns: --
 *
 * Description: Implements the quicksort algorithm
 *
 *****************************************************************************/

void quick_sort (Parking_spot a[], int n) 
{
	Parking_spot t;

    int i, j, p;
    if (n < 2)
        return;
    p = a[n / 2].distance;
    for (i = 0, j = n - 1;; i++, j--) {
        while (a[i].distance < p)
            i++;
        while (p < a[j].distance)
            j--;
        if (i >= j)
            break;
        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
    quick_sort(a, i);
    quick_sort(a + i, n - i);
}

/******************************************************************************
 * CreatesSpotsTable()
 *
 * Arguments: park
 *			 
 * Returns: spots matrix
 *
 * Description: Creates the matrix for the spots
 *
 *****************************************************************************/

Parking_spot ** CreatesSpotsTable(Park *p)
{
	int i;

	Parking_spot **spots_matrix = (Parking_spot **) malloc((p->S)*sizeof(Parking_spot *));

	if(spots_matrix == NULL)
	{
		fprintf((stderr), "Error in malloc of spots matrix.\n");
		exit(0);
	}

	for(i = 0; i < p->S; i++)
	{
		spots_matrix[i] = (Parking_spot *) malloc((p->Spots)*sizeof(Parking_spot));

		if(spots_matrix[i] == NULL)
		{
			fprintf(stderr, "Error in malloc of matrix.\n");
			exit(0);
		}
	}

	return spots_matrix;
}

/******************************************************************************
 * InsertSpotsMatrix()
 *
 * Arguments: park
 *            spots matrix
 *            parents vector
 *            weight vector
 *			 
 * Returns: --
 *
 * Description: Inserts the spots on the matrix
 *
 *****************************************************************************/

void InsertSpotMatrix(Park *p, Parking_spot ** spots_matrix, int st[], long int wt[])
{
	long int i, x = 0, y, pos;

	for(i = 0; i < p->G->V; i++)
	{
		if(p->G->node_info[i].type == EMPTY_SPOT || p->G->node_info[i].type == OCCUPIED)
		{
			for(y = 0; y < p->S; y++)
			{
				spots_matrix[y][x].node = i;
				spots_matrix[y][x].status = p->G->node_info[i].status;

				pos = Get_Pos(p->accesses[y].pos->x, p->accesses[y].pos->y, p->accesses[y].pos->z, p->N, p->M);
				GRAPHpfs(p->G, pos, st, wt, 0);
				spots_matrix[y][x].distance = 3*wt[i];
			}
			x++;
		}
	}

	for(y = 0; y < p->S; y++)
		quick_sort(spots_matrix[y], p->Spots);
		
}