#include <stdio.h>
#include <string.h>
#include "sorted-list.h"
#include "sorted-list.c"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

int main()
{
  SortedListPtr list = SLCreate(&compareInts);
  SortedListIteratorPtr iterator, iterator_nulltest, iterator_1, iterator_2;
  int *buffer;
  char *buffer_char;
  int i;
  int  *a, *b, *c, *d, *e;
  char *a_char, *b_char, *c_char, *d_char;
  if (list->head == NULL) { // Make sure list has been created correctly
    fprintf(stdout, "\nList created\n");
  }

  // Setting up {7,5,3} example from announcements
  // Will remove 5, then insert 4
  fprintf(stdout, "\nTest Case 1\n");
  a = (int*)malloc(sizeof(int));
  *a = 7;
  b = (int*)malloc(sizeof(int));
  *b = 5;
  c = (int*)malloc(sizeof(int));
  *c = 3;
  d = (int*)malloc(sizeof(int));
  *d = 4;
  SLInsert(list, a); 
  SLInsert(list, b); 
  SLInsert(list, c); 
  iterator = SLCreateIterator(list);
  fprintf(stdout, "Next Item: %d\n", *(int*)(SLNextItem(iterator)));
  fprintf(stdout, "Next Item: %d\n", *(int*)(SLNextItem(iterator)));
  i = SLRemove(list, b); fprintf(stdout, "Remove: %d ", *b);
  fprintf(stdout, "Remove returns (%d)\n", i);
  SLInsert(list, d); 
  fprintf(stdout, "Next Item: %d\n", *(int*)(SLNextItem(iterator)));
  SLDestroy(list);
  SLDestroyIterator(iterator);
  
  // Setting up {7,5,3} example from announcements
  // Will remove 5, then insert 6
  fprintf(stdout, "\nTest Case 2\n");
  list = SLCreate(&compareInts);
  iterator = SLCreateIterator(list);
  a = (int*)malloc(sizeof(int));
  *a = 7;
  b = (int*)malloc(sizeof(int));
  *b = 5;
  c = (int*)malloc(sizeof(int));
  *c = 3;
  d = (int*)malloc(sizeof(int));
  *d = 6;
  SLInsert(list, a); 
  SLInsert(list, b); 
  SLInsert(list, c); 
  fprintf(stdout, "Next Item: %d\n", *(int*)(SLNextItem(iterator)));
  fprintf(stdout, "Next Item: %d\n", *(int*)(SLNextItem(iterator)));
  i = SLRemove(list, b); fprintf(stdout, "Remove: %d ", *b);
  fprintf(stdout, "Remove returns (%d)\n", i);
  SLInsert(list, d); 
  fprintf(stdout, "Next Item: %d\n", *(int*)(SLNextItem(iterator)));
  SLDestroyIterator(iterator);


  // Removal Test
  // Already removed data, non-existent data, NULL pointer
  fprintf(stdout, "\nTest Case 3\n");
  e = (int*)malloc(sizeof(int));
  *e = 1000;
  i = SLRemove(list, b);
  fprintf(stdout, "Remove returns (%d)\n", i);
  i = SLRemove(list, e);
  fprintf(stdout, "Remove returns (%d)\n", i);
  i = SLRemove(list, NULL);
  fprintf(stdout, "Remove returns (%d)\n", i);

  SLDestroy(list);

  /*
  // Destroying something already destroyed
  fprintf(stdout, "Destruction Testing\n");
  fprintf(stdout, "Second List Destroy...\n");
  //SLDestroy(list);
  fprintf(stdout, "Second Iterator Destroy...\n");
  // SLDestroyIterator(iterator);
  */

  // Setting up to check sorting
  // insert 5, 7, 3, 10
  fprintf(stdout, "\nTest Case 4\n");
  list = SLCreate(&compareInts);
  iterator = SLCreateIterator(list);
  a = (int*)malloc(sizeof(int));
  *a = 1;
  b = (int*)malloc(sizeof(int));
  *b = 20;
  c = (int*)malloc(sizeof(int));
  *c = 17;
  d = (int*)malloc(sizeof(int));
  *d = 34;
  SLInsert(list, a); 
  SLInsert(list, b); 
  SLInsert(list, c); 
  SLInsert(list, d); 
  fprintf(stdout, "Next Item: %d\n", *(int*)(SLNextItem(iterator)));
  fprintf(stdout, "Next Item: %d\n", *(int*)(SLNextItem(iterator)));
  fprintf(stdout, "Next Item: %d\n", *(int*)(SLNextItem(iterator)));
  fprintf(stdout, "Next Item: %d\n", *(int*)(SLNextItem(iterator)));
  SLDestroy(list);
  SLDestroyIterator(iterator);

  // Push Iterator to end of list
  fprintf(stdout, "\nTest Case 5\n");
  list = SLCreate(&compareInts);
  iterator = SLCreateIterator(list);
  a = (int*)malloc(sizeof(int));
  *a = 1;
  b = (int*)malloc(sizeof(int));
  *b = 2;
  c = (int*)malloc(sizeof(int));
  *c = 3;
  d = (int*)malloc(sizeof(int));
  *d = 4;
  SLInsert(list, a); 
  SLInsert(list, b); 
  SLInsert(list, c); 
  SLInsert(list, d); 
  while ( ( buffer = (int*)(SLNextItem(iterator)) ) != NULL ) {
    fprintf(stdout, "Next Item: %d\n", *buffer);
  }
  SLDestroy(list);
  SLDestroyIterator(iterator);

  // Two iterators on single list
  fprintf(stdout, "\nTest Case 6\n");
  list = SLCreate(&compareInts);
  iterator_1 = SLCreateIterator(list);
  iterator_2 = SLCreateIterator(list);
  a = (int*)malloc(sizeof(int));
  *a = 1;
  b = (int*)malloc(sizeof(int));
  *b = 2;
  c = (int*)malloc(sizeof(int));
  *c = 3;
  d = (int*)malloc(sizeof(int));
  *d = 4;
  SLInsert(list, a); 
  SLInsert(list, b); 
  SLInsert(list, c); 
  SLInsert(list, d); 
  for (i = 0; i < 2; i++) {
    buffer = (int*)(SLNextItem(iterator_1));
    fprintf(stdout, "Iterator 1 Next Item: %d\n", *buffer);
  }
  while ( (buffer = (int*)(SLNextItem(iterator_2))) != NULL ) {
    fprintf(stdout, "Iterator 2 Next Item: %d\n", *buffer);
  }  
  while ( (buffer = (int*)(SLNextItem(iterator_1))) != NULL ) {
    fprintf(stdout, "Iterator 1 Next Item: %d\n", *buffer);
  }  
  SLDestroy(list);
  SLDestroyIterator(iterator_1);
  SLDestroyIterator(iterator_2);

  // Using different data types
  fprintf(stdout, "\nTest Case 7\n");
  list = SLCreate(&compareInts);
  iterator = SLCreateIterator(list);
  a_char = (char*)malloc(sizeof(char));
  *a_char = 'a';
  b_char = (char*)malloc(sizeof(char));
  *b_char = 'b';
  c_char = (char*)malloc(sizeof(char));
  *c_char = 'c';
  d_char = (char*)malloc(sizeof(char));
  *d_char = 'd';
  SLInsert(list, a_char); 
  SLInsert(list, b_char); 
  SLInsert(list, c_char); 
  SLInsert(list, d_char); 
  while ( (buffer_char = (char*)(SLNextItem(iterator))) != NULL ) {
    fprintf(stdout, "Next Item: %c\n", *buffer_char);
  }  
  SLDestroy(list);
  SLDestroyIterator(iterator);



  // Attempt to insert duplicate
  fprintf(stdout, "\nTest Case 8\n");
  list = SLCreate(&compareInts);
  iterator = SLCreateIterator(list);
  a = (int*)malloc(sizeof(int));
  *a = 1;
  b = (int*)malloc(sizeof(int));
  *b = 2;
  c = (int*)malloc(sizeof(int));
  *c = 3;
  d = (int*)malloc(sizeof(int));
  *d = 3;
  SLInsert(list, a); //fprintf(stdout, "Insert: %d\n", *a);
  SLInsert(list, b); //fprintf(stdout, "Insert: %d\n", *b);
  SLInsert(list, c); //fprintf(stdout, "Insert: %d\n", *c);
  i = SLInsert(list, d);
  fprintf(stdout, "Insert returns (%d)\n", i);
  while ( (buffer = (int*)(SLNextItem(iterator))) != NULL ) {
    fprintf(stdout, "Next Item: %d\n", *buffer);
  }  


  // Test some NULL pointers
  fprintf(stdout, "\nTest Case 9\n");
  a = (int*)malloc(sizeof(int));
  *a = 1;
  SLInsert(NULL, a);
  i = SLRemove(NULL, a);
  fprintf(stdout, "Remove returns (%d)\n", i);
  i = SLRemove(list, NULL);
  fprintf(stdout, "Remove returns (%d)\n", i);
  iterator_nulltest = SLCreateIterator(NULL);
  if (SLNextItem(iterator_nulltest) == NULL) {
    fprintf(stdout, "NULL Iterator\n");
  }
  return 1;
}
