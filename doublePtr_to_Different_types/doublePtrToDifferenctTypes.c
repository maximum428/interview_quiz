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

int main(void) {
    doublePtrToDifferentTypes();
    return 0;
}
