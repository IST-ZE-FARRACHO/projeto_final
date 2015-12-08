/******************************************************************************
 *
 * File Name: park_config.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 #ifndef park_config_H
 #define park_config_H

 #include "includes.h"

 Park *NewPark(int, int, int, int, int);

 int Char_to_Number (char c);

 void Get_edges(Park *p, int vector1[], int vector2[], int nr_columns, int y1, int y2, int _floor);

 void Map_to_Park_Graph (Park * p, FILE * f, int);

 void Read_Doors_info (Park * p, FILE * f, long int *, long int *);

 void Read_floor (Park * p, FILE * f, int, long int *, long int *);

 Park *ReadFilePark (char * file);

 void FreePark(Park * p);

 #endif
