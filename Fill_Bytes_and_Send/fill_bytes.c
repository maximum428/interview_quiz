#include <stdiolh>
#include <stdlib.h>

#define MIN(x, y)   x ^ ((x ^ y) & -(x < y))

void receive(const uint8_t *bytes, size_t nbytes) {
    static uint8_t buffer[16];
    static size_t curlength = 0;
    
    while (nbytes > 0) {
        size_t to_copy = MIN(16 - curlength, nbytes);
        memcpy(buffer + currlength, bytes, to_copy);
        
        curlength += to_copy;
        bytes += to_copy;
        nbytes -= to_copy;
        
        if (curlength == 16) {
            // send(buffer);
            printf("Sedn 16 bytes\n");
            curlength = 0;
        }
    }
}

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
    
    Data *data;
    method(fd, &data);
    
    fclose(fd);
    return 0;
}
