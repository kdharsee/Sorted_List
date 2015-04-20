#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "sorted-list.h"

// ptr->next == (*ptr).next
// REMEMBER . has higher precedence than *

SortedListPtr SLCreate(CompareFuncT cf) {
  SortedListPtr new_list = (SortedListPtr)malloc(sizeof(SortedList));
  SortedListNodePtr head = NULL; 
  CompareFuncT cmp_func = cf;
  new_list->head = head;
  new_list->cmp_func = cmp_func;
  return new_list;
}

void SLDestroy(SortedListPtr list) {
  if (list == NULL) {
    return;
  }
  if (list->head == NULL) {
    return;
  }
  SortedListNodePtr ptr;
  SortedListNodePtr prev;
  for (prev = list->head, ptr = list->head->next; ptr != NULL; prev = ptr, ptr = ptr->next) {
    // Will keep iterating till ptr falls off the list. When ptr is null, prev will be on the last element in the list
    free(prev->data);
    free(prev);
  }
  free(prev->data);
  free(prev);  
  list->head = NULL;
  free(list);
  list = NULL;
}

int SLInsert(SortedListPtr list, void *newObj) {
  // Assumes no duplicates are allowed
  if (list == NULL) {
    return 0;
  }
  if (newObj == NULL) {
    return 0;
  }

  SortedListNodePtr ptr = list->head;
  SortedListNodePtr new_node = (SortedListNodePtr)malloc(sizeof(SortedListNode));
  CompareFuncT cmp_func = list->cmp_func;
  if (list->head == NULL) { // If list is empty, create the first node here
    new_node->data = newObj;
    new_node->removed = 0;
    new_node->next = NULL;
    list->head = new_node;
    return 1;
  }
  if ( (*cmp_func)(ptr->data, newObj) == 0 ) { // If the node is already in the list, return with failure
    if (ptr->removed == 0) {
      return 0;
    }
    else {
      ptr->removed = 0;
      return 1;
    }
  }
  if ( (*cmp_func)(ptr->data, newObj) < 0 ) { // Check if newObj should be the new head
    new_node->data = newObj;
    new_node->removed = 0;
    new_node->next = ptr;
    list->head = new_node;
    return 1;
  }
  while (ptr->next != NULL) { // Iterate through the entire list except last node
    if ( (*cmp_func)(ptr->next->data, newObj) == 0 ) {
      if (ptr->next->removed == 0) {
	return 0;
      }
      else {
	ptr->next->removed = 0;
	return 1;
      }
    }
    else if ( (*cmp_func)(ptr->next->data, newObj) < 0 ) { // Check if the next object is smaller
      // Enter to put newobj before smaller object
      // Need to check if iterator is poitning at something that hs been removed. 
      new_node->data = newObj;
      new_node->removed = 0;
      new_node->next = ptr->next;
      ptr->next = new_node;
      return 1;
    }
    ptr = ptr->next;
  }
  // If program reached this point, nothing has been inserted.
  // Throw newObj on the end
  new_node->data = newObj;
  new_node->removed = 0;
  new_node->next = NULL;
  ptr->next = new_node;
  return 1;
}

int SLRemove(SortedListPtr list, void *newObj) { 
  if (list == NULL) {
    return 0;
  }
  if (list->head == NULL) {
    return 0;
  }
  if (newObj == NULL) {
    return 0;
  }
  SortedListNodePtr ptr = list->head;
  CompareFuncT cmp_func = list->cmp_func;
  while (ptr != NULL) { 
    if ( (*cmp_func)(ptr->data, newObj) == 0 ) { // Check for object at each node
      if (ptr->removed == 1) // Since no duplicates allowed, if it's removed it won't be down the list
	return 0;
      else {
	ptr->removed = 1; // Mark as removed
	return 1;
      }
    }
    ptr = ptr->next;
  }
  return 0;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
  if (list == NULL) {
    return NULL;
  }
  SortedListIteratorPtr new_iterator = (SortedListIteratorPtr)malloc(sizeof(SortedListIterator));
  new_iterator->current = NULL;
  new_iterator->list = list;
  return new_iterator;
}

void SLDestroyIterator(SortedListIteratorPtr iterator) {
  if (iterator == NULL) {
    return;
  }
  if (iterator->current == NULL) {
    return;
  }
  iterator->current = NULL;
  free(iterator);
  iterator = NULL;
}

void *SLNextItem(SortedListIteratorPtr iterator) {
  if (iterator == NULL) {
    return NULL;
  }
  if (iterator->list == NULL) {
    return NULL;
  }
  if (iterator->current == NULL) { // This will be true before the iterator takes first step
    iterator->current = iterator->list->head; // Move Iterator to head of list
    return iterator->current->data; 
  }
  while (iterator->current->next != NULL) { // Iterates till the end of list looking for the next non-removed node
    iterator->current = iterator->current->next;
    if (iterator->current->removed == 0) {
      return iterator->current->data;
    }
  }
  // Reaching this point means iterator has come to the end of the list
  return NULL;
}
