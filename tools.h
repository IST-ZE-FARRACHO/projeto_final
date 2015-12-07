/******************************************************************************
 *
 * File Name: tools.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

#ifndef ToolsHeader
#define ToolsHeader

#include "includes.h"
 
 /******************************************************************************
 * AbreFicheiro ()
 *
 * Arguments: nome - pointer to string containing name of file to open
 *            mode - mode to use to open the file
 * Returns: FILE * - handle to file opened
 * Side-Effects: input file is opened
 *
 * Description: Open file for reading, returns handle
 *
 *****************************************************************************/

FILE *AbreFicheiro(char *name, char *mode);
void FechaFicheiro(FILE * f);
LinkedList * ListCreator();
int Get_Pos(int, int, int, int, int);
int SamePos(Position * pos1, Position * pos2);
void exch(int *i, int *j);
int escreve_saida(FILE *fp, char *vid, int tk, int pX, int pY, int pZ, char tm);
int LessNumRest(Item a, Item b); /*If a < b return 1*/

 /* End of: Protect multiple inclusions                              */
#endif