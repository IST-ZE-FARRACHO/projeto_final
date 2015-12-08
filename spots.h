/******************************************************************************
 *
 * File Name: spots.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 #ifndef spots_H
 #define spots_H

 #include "includes.h"

void quick_sort (Parking_spot a[], int n);
Parking_spot ** CreatesSpotsTable(Park *p);
void InsertSpotMatrix(Park *p, Parking_spot ** spots_matrix, int st[], long int wt[]);

 #endif