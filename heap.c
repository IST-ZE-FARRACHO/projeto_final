/******************************************************************************
 *
 * File Name: heap.c
 *	      (c) 2010 AED
 * Author:    AED team
 * Revision:  v2.3 ACR
 *
 * NAME
 *     Heap11 - Heap operations
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <malloc.h>
 *
 * DESCRIPTION
 *		implements tree auxiliary functions
 * DIAGNOSTICS tested
 *
 *****************************************************************************/

#include "includes.h"

/******************************************************************************
 * FixUp()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixup
 * Returns:
 * Side-Effects: none
 *
 * Description: Performs fixup from index
 *
 *****************************************************************************/

void FixUp(Heap * h, int k)
{
  Item t;
  while ((k > 0) && (h->less) ((h->heapdata)[(k - 1) / 2], (h->heapdata)[k])) {
#ifdef DEMO
#endif
    /*---------------------------------------------------------*/
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[(k - 1) / 2];
    (h->heapdata)[(k - 1) / 2] = t;

#ifdef DEMO
#endif
    /*---------------------------------------------------------*/
    k = (k - 1) / 2;
  }

  return;
}


/******************************************************************************
 * FixDown()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixdown
 * Returns:
 * Side-Effects: none
 *
 * Description: performs fixdown from index
 *
 *****************************************************************************/

void FixDown(Heap * h, int k)
{
  int j;
  Item t;

  while ((2 * k + 1) < h->n_elements) 
  {

    j = 2 * k + 1;

    if (((j + 1) < h->n_elements) && (h->less) (h->heapdata[j], h->heapdata[j + 1])) 
    {
      /* second offspring is greater */
      j++;
    }
    
    if (!(h->less) (h->heapdata[k], h->heapdata[j])) 
    {
      /* Elements are in correct order. */

#ifdef DEMO
#endif
      break;
    }
#ifdef DEMO
#endif
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[j];
    (h->heapdata)[j] = t;
    k = j;

#ifdef DEMO
#endif
  }

  return;
}

/******************************************************************************
 * FixDown()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixdown
 * Returns:
 * Side-Effects: none
 *
 * Description: performs fixdown from index
 *
 *****************************************************************************/

void FixDownPQ(Heap * h, int k, long int vector[])
{
  int j;
  Item t;

  while ((2 * k + 1) < h->n_elements) 
  {

    j = 2 * k + 1;

    if (((j + 1) < h->n_elements) && (h->less) ((Item) vector[j], (Item) vector[j + 1])) 
    {
      /* second offspring is greater */
      j++;
    }
    
    if (!(h->less) ((Item) vector[k], (Item) vector[j])) 
    {
      /* Elements are in correct order. */

#ifdef DEMO
#endif
      /*---------------------------------------------------------*/
      break;
    }
#ifdef DEMO
#endif
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[j];
    (h->heapdata)[j] = t;
    k = j;

#ifdef DEMO
#endif
  }

  return;
}



/******************************************************************************
 * NewHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 * Side-Effects: none
 *
 * Description: allocates space for a new heap of specified size
 *
 *****************************************************************************/

Heap *NewHeap(int size, int (*less) (Item, Item))
{
  Heap *h;

  h = (Heap *) malloc(sizeof(Heap));

  if (h == ((Heap *) NULL)) 
  {
    exit(0);
  }

  h->n_elements = 0;
  h->less = less;
  h->size = size;
  h->heapdata = (Item *) malloc(size * sizeof(Item));

  if (h->heapdata == ((Item *) NULL)) 
  {
    exit(0);
  }

  return (h);
}

/******************************************************************************
 * NewHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 * Side-Effects: none
 *
 * Description: allocates space for a new heap of specified size
 *
 *****************************************************************************/


/******************************************************************************
 * Insert()
 *
 * Arguments: h - pointer to heap
 *            element - pointer to new element
 * Returns: vopid
 * Side-Effects: none
 *
 * Description: add element at the end of heap and do fixup
 *
 *****************************************************************************/

int Insert(Heap * h, Item element)
{
  if (h->n_elements == h->size) {
    return 0;
  }
  h->heapdata[h->n_elements] = element;

  h->n_elements++;
  FixUp(h, h->n_elements - 1);

  return 1;
}

/******************************************************************************
 * InsertNum()
 *
 * Arguments: h - pointer to heap
 *            i - number
 * Returns: vopid
 * Side-Effects: none
 *
 * Description: add element at the end of heap and do fixup
 *
 *****************************************************************************/


void InsertNum(Heap * h, long int i)
{
  Insert(h, (Item) i);

  return;
}

/******************************************************************************
 * Direct_Insert()
 *
 * Arguments: h - pointer to heap
 *            element - pointer to new element
 * Returns: vopid
 * Side-Effects: none
 *
 * Description: add element at the end of heap but does not perform fixup
 *
 *****************************************************************************/

int Direct_Insert(Heap * h, Item element)
{
  if (h->n_elements == h->size) {
    return 0;
  }
  h->heapdata[h->n_elements] = element;

  h->n_elements++;


  return 1;
}

/******************************************************************************
 * Modify()
 *
 * Arguments: h - pointer to heap
 *            index - index of element to modify
 *            newvalue - new element value
 * Returns: void
 * Side-Effects: none
 *
 * Description: compares new element with antecedent, if larger do a fixup
 *              otherwise do fixdown
 *
 *****************************************************************************/

void Modify(Heap * h, int index, Item newvalue)
{
  if (index > h->n_elements - 1) {
    return;
  }
  /* Compares new value  with the value of the element to substitute */
  if ((h->less) (newvalue, h->heapdata[index])) {
    /* If smaller, reconstruct heap with function FixDown */
    free(h->heapdata[index]);
    h->heapdata[index] = newvalue;
    FixDown(h, index);
  }
  else {
    /* If greater, reconstruct heap using the function FixUp */
    free(h->heapdata[index]);
    h->heapdata[index] = newvalue;
    FixUp(h, index);
  }

  return;
}


/******************************************************************************
 * RemoveMax()
 *
 * Arguments: h - pointer to heap
 * Returns: Item
 * Side-Effects: none
 *
 * Description: exchange first and last element of heap, remove last element
 *              (max element) from heap and maintain heap order by performing
 *              a fixdown of the first element
 *
 *****************************************************************************/

Item RemoveMax(Heap * h)
{
  Item t;

  if (h->n_elements > 0) {
    t = (h->heapdata)[0];
    (h->heapdata)[0] = (h->heapdata)[h->n_elements - 1];
    (h->heapdata)[h->n_elements - 1] = t;
    free(h->heapdata[h->n_elements - 1]);
    h->n_elements--;
    FixDown(h, 0);
    return t;
  }

  return NULL;
}

/******************************************************************************
 * RemoveMin()
 *
 * Arguments: Heap
 *            vector
 * Returns: none
 * Side-Effects: None
 *
 * Description: cleans an heap
 *
 *****************************************************************************/

long int RemoveMin(Heap * h, long int vector[])
{
  long int i, men = 0;
  Item t;

  for(i = 0; i < h->n_elements; i++)
    if(vector[(long int) h->heapdata[i]] <= vector[(long int) h->heapdata[men]])
      men = i;       

  i = (long int) h->heapdata[men];

  t = (h->heapdata)[men];
  (h->heapdata)[men] = (h->heapdata)[h->n_elements - 1];
  (h->heapdata)[h->n_elements - 1] = t;

  /*free(h->heapdata[h->n_elements -1]);*/
  h->n_elements--;
  FixDownPQ(h, i, vector);

  return i;
}

/******************************************************************************
 * CleanHeap()
 *
 * Arguments: Heap
 * Returns: none
 * Side-Effects: None
 *
 * Description: cleans an heap
 *
 *****************************************************************************/

void CleanHeap(Heap * h)
{
    for(; h->n_elements > 0; h->n_elements--)
    	free(h->heapdata[h->n_elements-1]);

    return;
}

/******************************************************************************
 * FreeHeap()
 *
 * Arguments: Heap
 * Returns: none
 * Side-Effects: None
 *
 * Description: frees the heap
 *
 *****************************************************************************/

void FreeHeap(Heap *h)
{
   CleanHeap(h);
   free(h->heapdata);
   free(h);

}

/******************************************************************************
 * VerifyHeap()
 *
 * Arguments: Heap
 * Returns: int (1 if it is an heap; 0 otherwise)
 * Side-Effects: None
 *
 * Description: verifies if the argument satisfies the heap condition
 *
 *****************************************************************************/

int VerifyHeap(Heap * h)
{
    int i;

    for(i = 0; i < (h->n_elements-1)/2; i++)
    	if (!(h->less) (h->heapdata[i], h->heapdata[2*i+1]))
    		return 1;

    return 0;
}

/******************************************************************************
 * Heapify()
 *
 * Arguments: Heap
 * Returns: void
 * Side-Effects:
 *
 * Description: forces the argument to be an heap
 *
 *****************************************************************************/

void Heapify(Heap * h)
{
    int aux = 0;

    for(aux = (h->n_elements - 1)/2; aux >= 0; aux--)
      FixDown(h, aux);

  return;
}

/******************************************************************************
 * HeapEmpty()
 *
 * Arguments: Heap
 * Returns: void
 * Side-Effects:
 *
 * Description: checks if an heap is empty
 *
 *****************************************************************************/

int HeapEmpty(Heap * h)
{
  if(h->n_elements == 0)
    return 1;

  return 0;
}



