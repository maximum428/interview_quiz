#include<stdio.h>
#include <stdint.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void receive(uint8_t *bytes, uint8_t nbytes) {
    static int curlength = 0;
    int i, size;
    int* curbytes = malloc(16 * sizeof(uint8_t));
    
    while (nbytes > 0) {
#if 1
        size += MIN(16-curlength, nbytes);
        for (i = 0; i < size; i++) {
            curbytes[i] = bytes[i];
        }
        curlength += size;
#else
        curlength += MIN(16-curlength, nbytes);
        for (i = 0; i < nbytes; i++) {
            curbytes[i] = bytes[i];
        }
#endif
        nbytes = nbytes - 16 < 0 ? 0 : nbytes-16;
        printf("Accumulate bytes: %d, %d\n", curlength, nbytes);
        if (curlength == 16) {  // reach to 16, send it
            //send(curbytes);
            printf("Send 16 bytes\n");
            curlength = 0;
        } 
    }
}

int main(void) {
    uint8_t *bytes = malloc(16 * sizeof(uint8_t));
    
    receive(&bytes, 8);
    return 0;
}
