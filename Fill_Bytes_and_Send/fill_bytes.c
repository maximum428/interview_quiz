#include <stdiolh>
#include <stdlib.h>

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
