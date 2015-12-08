/******************************************************************************
 *
 * File Name: restrictions.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

#ifndef Restrictions_H
#define Restrictions_H

#include "includes.h"
 
Restrictions *NewRestrictions(int rest_type, int ta, char inout, int x, int y, int z);
LinkedList * ReadRestrictsFile(char * file, LinkedList * restrictionslist);
void UpdateRestrictions(LinkedList * restrictionslist, Park * park, Car * new, Parking_spot ** spots_matrix);

#endif