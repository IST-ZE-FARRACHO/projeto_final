/******************************************************************************
 *
 * File Name: includes.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION file with the includes and defines informations
 *
 *****************************************************************************/

#ifndef includes_H
#define includes_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "tools.h"
#include "graph.h"
#include "cars.h"
#include "restrictions.h"
#include "LinkedList.h"
#include "park_config.h"
#include "heap.h"
#include "spots.h"

#define ROAD 0
#define WALL 1
#define ENTRY_DOOR 2
#define PED_ACCESS 3
#define EMPTY_SPOT 4
#define OCCUPIED 5
#define RAMP_UP 6
#define RAMP_DOWN 7
#define NAME_SIZE 15

#define NORMAL_TIME 1
#define RAMP_TIME 2

#define CAN_GO 0
#define CANT_GO 1

#define DONTCARE 0
#define POSITION 0
#define FLOOR 1

#define POSITIONREST 0
#define FLOORREST 1

#define MAX_ID_SIZE 128

#endif