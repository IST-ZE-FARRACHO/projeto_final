/*
 *  File name: LinkedList.c
 *
 *  Author: 2013 Fall Semester AED Team
 *
 *  Release date: 2013/10/04
 *
 *  Description: C-Implementation of an Abstract Linked List
 *
 *  Implementation details:
 *    Linked list node: Each node of the list contains a pointer to
 *   the item stored in the node and a pointer to the next node. The
 *   item is specified in the file defs.h.
 *
 *  Version: 1.0
 *
 *  Change log: N/A
 *
 */



/* Header Inclusions                                              */
#include <stdio.h>
#include <stdlib.h>



/* Include Header File with Data Type and Function Prototypes     */
#include "LinkedList.h"


/*
 *  Function:
 *    initLinkedList
 *
 *  Description:
 *    Initializes a new linked list.
 *
 *  Arguments:
 *    None
 *
 *  Return value:
 *    Returns the pointer to a new linked list.
 */

LinkedList * initLinkedList(void)
{
  return NULL;
}

/*
 *  Function:
 *    freeLinkedList
 *
 *  Description:
 *    Frees the memory allocated to a linked list.
 *
 *  Arguments:
 *    Pointer to the first element of a linked list:
 *      (LinkedList *) first
 *    Function to free the memory allocated to the items:
 *      void freeItem(Item)
 *
 *  Return value:
 *    None
 */
void freeLinkedList(LinkedList * first, void (* freeItemFnt)(Item))
{
  LinkedList * next;
  LinkedList * aux;
  
  /* Cycle from the first to the last element                     */
  for(aux = first; aux != NULL; aux = next) 
  {
    /* Keep trace of the next node                                */
    next = aux->next;

    /* Free current item                                          */
  /*    freeItemFnt(aux->this);*/
    free(aux->this);

    /* Free current node                                          */
    free(aux);
  }

  return;
}



/*
 *  Function:
 *    lengthLinkedList
 *
 *  Description:
 *    Determines the length of a linked list.
 *
 *  Arguments:
 *    Pointer to the first node of the linked list:
 *        (LinkedList *) first
 *
 *  Return value:
 *    Returns the length of the linked list.
 */
int lengthLinkedList(LinkedList * first)
{

  int counter = 0;

  /* Length determination cycle                                   */
  while(first != NULL)
  {

    counter++;
    first=first->next;

  }

  return counter;
}


/*
 *  Function:
 *    getNextNodeLinkedList
 *
 *  Description:
 *    Returns the next node of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the next node of a linked list. NULL
 *   is returned in case the current node is empty or there is no
 *   node following the current node.
 */

LinkedList * getNextNodeLinkedList(LinkedList * node)
{
  return ((node == NULL) ? NULL : node->next);
}



/*
 *  Function:
 *    getItemLinkedList
 *
 *  Description:
 *    Gets the item of a linked list node.
 *
 *  Arguments:
 *    Pointer to a linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the item of a linked list node. NULL
 *   is returned if the node is NULL (or if the item is NULL).
 */

Item getItemLinkedList(LinkedList * node)
{
  /* Check if node is not empty                                   */
  if(node == NULL)
    return NULL;

  return node->this;
}

LinkedList * EditItemLinkedList(LinkedList * node, Item value)
{
  /* Check if node is not empty                                   */
  if(node == NULL)
    return NULL;

  node->this = value;

  return node;
}



/*
 *  Function:
 *    insertUnsortedLinkedList
 *
 *  Description:
 *    Creates a new linked list node.
 *
 *  Arguments:
 *    Item to associate to the new node:
 *      Item this
 *    Pointer to the next node:
 *      (LinkedList *) next
 *
 *  Return value:
 *    Returns the pointer to the node.
 */
 
LinkedList * insertUnsortedLinkedList(LinkedList * next, Item this)
{
  LinkedList * new;

  /* Memory allocation                                            */
  new = (LinkedList *) malloc(sizeof(LinkedList));

  /* Check memory allocation errors                               */
  if(new == NULL)
    return NULL;

  /* Initialize new node                                          */
  new->this = this;
  new->next = next;

  return new;
}




/*
 *  Function:
 *    insertSortedLinkedList
 *
 *  Description:
 *    Inserts an item in order in an sorted linked list.
 *
 *  Arguments:
 *    Pointer to the first node of a sorted linked list:
 *        (LinkedList *) first
 *    Pointer to item to be inserted:
 *        Item item
 *    Pointer to function to compare two items:
 *        int comparisonItemFnt(void * item1, void * item2)
 *
 *        This function returns a value less, equal, or greater
 *       than zero if item1 compares less, equal, or greater than
 *       item2, respectively.
 *
 *    Pointer to integer to write error return value:
 *        (int *) err
 *
 *        0 upon sucess, 1 in case the item is NULL, and 2 in
 *   case of memory allocation failure.
 *
 *  Return value:
 *    Returns the pointer to the first node of the sorted linked list.
 */

LinkedList * insertSortedLinkedList(LinkedList * first, Item item, int (* comparisonItemFnt) (Item item1, Item item2), int * err)
{
  LinkedList * new;
  LinkedList * aux;
  LinkedList * tmp;
  aux = first;

  /* Memory allocation                                            */
  new = (LinkedList *) malloc(sizeof(LinkedList));
  new->this = item;

  /* Check memory allocation errors                               */
  if (new == NULL) 
  {
    fprintf(stderr, "Error in malloc of linkedlist.\n");
    exit(0);
  }

  /* Íf new is the first node of the list*/
  if( first == NULL)
  {
    first = new;
    return first;
  }

  /* Searching the best place to insert the node */ 
  while (aux != NULL)
  {
    /* if function returns 1 then new found its place*/
    if(comparisonItemFnt(new->this, aux->this) == 1)
    {

      if(aux == first)
      {
        new->next = first;
        new = first;
      }

      else
      {
        tmp->next = new;
        new->next = aux;
      }
      break;
    }
    else
    {
      tmp = aux;
      aux = aux->next;
    }
  }

  if(aux == NULL)
  {
      tmp->next = new;
      new->next = NULL;
  }

  return first;
}

