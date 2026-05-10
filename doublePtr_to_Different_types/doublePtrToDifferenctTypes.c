#include<stdio.h>

void doublePtrToDifferentTypes() {
    int a = 12;
    void *int_ptr = &a;
    float b = 5.2;
    void *float_ptr = &b;
    
    void **v_ptr = &int_ptr;
    printf("%d\n", *(int*)*v_ptr);
    v_ptr = &float_ptr;
    printf("%.2f\n", *(float*)*v_ptr);
}

void demo() {
  int a = 12;
  int* int_ptr = &a;
  printf("%d\n", *int_ptr);

  a = 13;
  printf("%d\n", *int_ptr);

  void* v_ptr = int_ptr;
  *(int*)v_ptr = 14;
  printf("%d\n", *int_ptr);
  printf("%d\n", a);
  printf("%d\n", *(int*)v_ptr);

  void **vv_ptr = (void*)&int_ptr;  // or &v_ptr
  *(int*)*vv_ptr = 15;
  printf("%d\n", *(int*)*vv_ptr);
  printf("%d\n", *(int*)v_ptr);
  printf("%d\n", *int_ptr);
  printf("%d\n", a);

  void ***vvv_ptr = &vv_ptr;
  *(int*)**vvv_ptr = 16;
  printf("%d\n", *(int*)**vvv_ptr);
  printf("%d\n", *(int*)*vv_ptr);
  printf("%d\n", *(int*)v_ptr);
  printf("%d\n", *int_ptr);
  printf("%d\n", a);

  float b = 3.2;
  float* float_ptr = &b;
  printf("%.2f\n", *float_ptr);
  v_ptr = float_ptr;
  printf("%.2f\n", *(float*)v_ptr);
  vv_ptr = &v_ptr;
  printf("%.2f\n", *(float*)*vv_ptr);
  printf("%.2f\n", *(float*)**vvv_ptr);
}

int main(void) {
    doublePtrToDifferentTypes();
    return 0;
}
/********************************************************/
/* Pointer expressions: ptr++,*ptr++, ++*ptr and *++ptr */

#include <stdio.h>

int main(void) {
  char *ptr = "alex chang";
  printf("%p\n", (void*)ptr);
  printf("%c\n", *ptr);
  printf("%c\n", *ptr++);
  printf("%c\n", *ptr);
  printf("%p\n", (void*)ptr);
  printf("%p\n", ptr+1);
  printf("%p\n", ptr++);
  printf("%p\n", (void*)ptr);
  printf("%c\n", *ptr);
  //printf("%d\n", ++*ptr);  
  /* Error: can be undefined behavior (Segment fault, bus error or crash) because In C, 
     string literals are usually stored in read-only memory which attempts to modify the first character of the string literal from 'e' to 'f'.  
     You can use Use a writable char array (char ptr[] = "alex chang") to fix it */

  printf("%c\n", *++ptr);

  return 0;
}
/* Output:
0x5615fa18c720
a
a
l
0x5615fa18c721
0x5615fa18c722
0x5615fa18c721
0x5615fa18c722
e
x
*/

/************************************************************/
/* wild/void pointer, NULL pointer, Generic pointer (Near pointer, Far pointer and Huge pointer are obsolete. modern 32/64 bit system does not support */

#include <stdio.h>
#include <stdlib.h>

#define Datatype int

int main(void) {
  //Datatype *ptr; // it is a wild/bad pointer, not initialize with any variable address
  //*ptr = NULL; // it is a NULL pointer

  /*
  Datatype *ptr = 10;  Error:  you assign the address to 10 instead of value
  Fix:
  Datatype value = 10;
  Datatype *ptr = &value;
  *ptr = 11; */

  Datatype *ptr = malloc(sizeof(Datatype));
  *ptr = 10;

  printf("%d\n", *ptr);
  *ptr = 12;
  
  free(ptr);
  printf("%d\n", *ptr); // become dangling pointer now

  void *ptr1;  // Generic pointer

  return 0;
}

/************************************************************************/
/* Array, pointer */

#include <stdio.h>
#include <stdlib.h>

#define Datatype int

int main(void) {
  Datatype *a[10];  // An array of 10 pointers to int. Each element stores an int*
  //Datatype (*b)[10]; // A pointer to an array o 10 ints
  //Datatype *(a[10]);  // An array of 10 pointers to int. Same as declaration #1

  for (int i = 0; i < 10; i++) {
    Datatype n = i + 1;
    a[i] = &n;
    printf("%p\n", a[i]);
    printf("%d\n", *a[i]);
  }

  Datatype x = 10, y = 20, z = 30;

  a[0] = &x;
  a[1] = &y;
  a[2] = &z;

  printf("%d\n", *a[0]);
  printf("%d\n", *a[1]);
  printf("%d\n", *a[2]);


  int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  Datatype (*b)[10] = &arr; // A pointer to an array o 10 ints = &arr;

  printf("%d\n", (*b)[0]);
  printf("%d\n", (*b)[5]);


  int w = 100;

  int *(c[10]);
  c[0] = &w;
  printf("%d\n", *c[0]);

  return 0;
}
