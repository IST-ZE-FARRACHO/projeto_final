/******************************************************************************
 *
 * File Name: cars.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

#ifndef CarsHeader
#define CarsHeader

#include "includes.h"
 
Car * NewCar(char * id, int ta, char type, char inout, int xs, int ys, int zs);

LinkedList * DeleteCarFromList(LinkedList * list, char *, int *, int *, int *);

void WriteParkPath(FILE *fp, Park * p, Car * new, Parking_spot ** spots_matrix, LinkedList ** carlist, LinkedList * wait_carlist, int st[], long int wt[]);

void ReadMoveCars(Park * p, char * file, Parking_spot ** spots_matrix, LinkedList * carlist, LinkedList * wait_carlist, int st[], long int wt[], LinkedList * restrictionlist, int);

int CheckEntrance(Park * p, int x, int y, int z);

Car * NewCar(char * id, int ta, char type, char inout, int xs, int ys, int zs);


/* End of: Protect multiple inclusions                              */
#endif