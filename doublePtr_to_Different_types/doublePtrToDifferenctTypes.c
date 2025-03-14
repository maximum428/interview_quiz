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
