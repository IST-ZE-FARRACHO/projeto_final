/*
 *  File name: LinkedList.h
 *
 *  Author: 2013 Fall Semester AED Team
 *
 *  Release date: 2013/10/04
 *
 *  Description: Header file for an Abstract Implementation of a
 *               Linked List
 *
 *  Data type list:
 *    Linked list node: LinkedList
 *
 *  Function list:
 *    A) Initialization & Termination
 *        initLinkedList
 *        freeLinkedList
 *
 *    B) Properties
 *        lengthLinkedList
 *
 *    C) Navigation
 *        getNextNodeLinkedList
 *
 *    D) Lookup
 *        getItemLinkedList
 *
 *    E) Insertion
 *        insertUnsortedLinkedList
 *
 *    F) Sorted linked lists
 *       insertSortedLinkedList
 *
 *  Dependencies:
 *    stdio.h
 *    stdlib.h
 *    defs.h
 *
 *  Version: 1.0
 *
 *  Change log: N/A
 *
 */


/* Prevent multiple inclusions                                      */
#ifndef LinkedListHeader
#define LinkedListHeader



/* Include Header File for the definition of the Item type        */
#include "includes.h"


LinkedList * initLinkedList(void);

void freeLinkedList(LinkedList * first);

int lengthLinkedList(LinkedList * first);

LinkedList * getNextNodeLinkedList(LinkedList * node);

Item getItemLinkedList(LinkedList * node);

LinkedList * EditItemLinkedList(LinkedList * node, Item value);

LinkedList * insertUnsortedLinkedList(LinkedList * next, Item this);

LinkedList * insertSortedLinkedList(LinkedList * first, Item item, int (* comparisonItemFnt) (Item item1, Item item2));



/* End of: Protect multiple inclusions */
#endif
