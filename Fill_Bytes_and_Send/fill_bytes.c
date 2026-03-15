#include <stdiolh>
#include <stdlib.h>

#define MIN(x, y)   y ^ ((x ^ y) & -(x < y))
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

/***************** C++ versin ********************/
#include <iostream>
#include <fstream>
#include <array>
#include <cstring>

using namespace std;

constexpr size_t BYTES_SIZE = 16;

void sendBuffer(const array<uint8_t, BYTES_SIZE>& buffer) {
  // TODO: replace with real send logic
  cout << "send " << buffer.size() << " bytes\n";
}

void receive(const uint8_t *bytes, size_t nbytes) {
  static array<uint8_t, BYTES_SIZE> buffer{};
  static size_t curLength = 0;

  while (nbytes > 0) {
    size_t toCopy = min(BYTES_SIZE - curLength, nbytes);

    memcpy(buffer.data() + curLength, bytes, toCopy);

    curLength += toCopy;
    bytes += toCopy;
    nbytes -= toCopy;

    if (curLength == BYTES_SIZE) {
      sendBuffer(buffer);
      curLength = 0;
    }
  }
}

struct Data {
  int val{};
  char name[128]{};
};

void sendData(const Data& data) {
  cout << "sendData: val = " << data.val << ", name = " << data.name << '\n';
}

bool readData(istream& is, Data& data) {
  size_t total = 0;
  auto* ptr = reinterpret_cast<char*>(&data);

  while (total < sizeof(Data)) {
    is.read(ptr + total, static_cast<streamsize>(sizeof(Data) - total));
    streamsize n = is.gcount();

    if (n <= 0) {
      if (is.eof()) {
        cerr << "Unexpected EOF\n";
      } else {
        cerr << "Read error\n";
      }
      return false;
    }
    total += static_cast<size_t>(n);
  }
  sendData(data);
  return true;
}

int main() {
  uint8_t data[] = {
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 10,
    11, 12, 13, 14, 15,
    16, 17, 18, 19, 20
  };
  receive(data, 5);       // 5 bytes
  receive(data + 5, 7);   // 7 bytes
  receive(data + 12, 8);  // 8 bytes

  ifstream input("input.bin", ios::binary);
  if (!input) {
    cerr << "Failed to open input.bin\n";
    return 1;
  }

  Data data1;
  if (!readData(input, data1)) {
    return 1;
  }

  return 0;
}
