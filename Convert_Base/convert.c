#include<stdio.h>

char *convert(unsigned int num, int base) {
    static char buff[33];
    char *ptr = &buff[sizeof(buff)-1];
    *ptr = '\0';
    
    do {
        *--ptr = "0123456789abcdef"[num % base];
        num /= base;
    } while (num != 0);
    return ptr;
}

int main(void) {
    char *s;
    s = convert(128, 16);
    
    printf("%s\n", s);
    return 0;
}
