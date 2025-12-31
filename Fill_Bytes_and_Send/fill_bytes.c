#include <stdiolh>
#include <stdlib.h>

#define MIN(x, y)   x ^ ((x ^ y) & -(x < y))
#define BYTES_SIZE  16

void receive(const uint8_t *bytes, size_t nbytes) {
    static uint8_t buffer[BYTES_SIZE];
    static size_t curlength = 0;
    
    while (nbytes > 0) {
        size_t to_copy = MIN(BYTES_SIZE - curlength, nbytes);
        memcpy(buffer + currlength, bytes, to_copy);
        
        curlength += to_copy;
        bytes += to_copy;
        nbytes -= to_copy;
        
        if (curlength == BYTES_SIZE) {
            // send(buffer);
            printf("Send %d bytes\n", BYTES_SIZE);
            curlength = 0;
        }
    }
}

typedef struct {
    int val;
    char name[128];
} Data;

void method(FILE *fd, Data *data) {
    size_t total = 0;
    unsigned char *ptr = (unsigned char*)data;
    
    while (total < sizeof(Data)) {
        size_t n = fread(ptr + total, 1, sizeof(Data) - total, fd);
        if (n == 0) {
            if (feof(fd)) {
                fprintf(stderr, "Unexpected EOF\n");
            } else {
                perror("fread");
            }
            return;
        }
        total += n;
    }
    
    sendData(data);
}

int main() {
    FILE *fd = fopen("input.bin", "rb");
    if (!fd) {
        perror("fopen");
        return 1;
    }
    
    Data data;
    method(fd, &data);
    
    fclose(fd);
    return 0;
}
