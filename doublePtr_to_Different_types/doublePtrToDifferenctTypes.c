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
    void* int_ptr = &a;
    a = 13;
    void *v_ptr = int_ptr;
    *(int*)v_ptr = 14;
    void **vv_ptr = &int_ptr;
    *(int*)*vv_ptr = 15;
    void ***vvv_ptr = &vv_ptr;
    *(int*)**vvv_ptr = 16;
    
    cout << *(int*)v_ptr << endl;
    cout << *(int*)*vv_ptr << endl;
    cout << *(int*)**vvv_ptr << endl;
    
    floa b = 3.2;
    void *float_ptr = &b;
    v_ptr = float_ptr;
    vv_ptr = &v_ptr;
    
    cout << *(float*)float_ptr << endl;
    cout << *(float*)v_ptr << endl;
    cout << *(float*)*vv_ptr << endl;
    cout << *(float*)**vvv_ptr << endl;
}

int main(void) {
    doublePtrToDifferentTypes();
    return 0;
}
