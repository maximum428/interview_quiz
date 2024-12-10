#include <iostream>
#include <cstdint>
#include <cstring>

#define UART0_BASE    0x4000c00
#define UART_DR       *((volatile uint32_t*)(UART0_BASE + 0x00))
#define UART_FR       *((volatile uint32_t*)(UART0_BASE + 0x18))
#define UART_IBRD     *((volatile uint32_t*)(UART0_BASE + 0x24))
#define UART_FBRD     *((volatile uint32_t*)(UART0_BASE + 0x28))
#define UART_LCRH     *((volatile uint32_t*)(UART0_BASE + 0x2C))
#define UART_CTL      *((volatile uint32_t*)(UART0_BASE + 0x30))

#define UART_FR_TXFF      (1 << 5)
#define UART_FR_RXFE      (1 << 4)
#define UART_CTL_UARTEN   (1 << 0)

#define SYSTEM_CLOCK    16000000
#define BAUD_RATE       9600

using namespace std;

class UART {
public:
  UART(uint32_t baseAddress = UART0_BASE) : uartBase(baseAddress) {
    init();
  }
  void init() {
    uint32_t baudDivisor = SYSTEM_CLOCK / (16 * BAUD_RATE);
    uint32_t fractionalDivisor = (SYSTEM_CLOCK % (16 * BAUD_RATE)) * 64 + (BAUD_RATE / 2);

    UART_IBRD = baudDivisor;
    UART_FBRD = fractionalDivisor;

    UART_LCRH = (1 << 5) | (1 << 6);
    UART_CTL = UART_CTL_UARTEN;
  }

  bool isTransmitReady() const {
    return (UART_FR & UART_FR_TXFF) == 0;
  }

  bool isReceiveReady() const {
    return (UART_FR & UART_FR_RXFE) == 0;
  }

  void sendByte(uint8_t data) {
    while (!isTransmitReady()) {

    }
    UART_DR = data;
  }

  uint8_t receiveByte() {
    while (!isReceiveReady()) {

    }
    return static_cast<uint8_t>(UART_DR & 0xFF);
  }

  void sendString(const string& str) {
    for (const auto& c : str) {
      sendByte(static_cast<uint8_t>(c));
    }
  }

  void receiveString(char* buffer, uint32_t maxLen) {
    uint32_t i = 0;
    while (i < maxLen - 1) {
      char c = static_cast<char>(receiveByte());
      if (c == '\n' || c == '\r') {
        break;
      }
      buffer[i++] = c;
    }
    buffer[i] = '\0';

  }
private:
  uint32_t uartBase;
};

int main() {
  UART uart;

  uart.sendString("Hello, UART from C++!\n");

  char receviedData[100];
  uart.receiveString(receviedData, sizeof(receviedData));

  cout << "Received: " << receviedData << endl;

  while (true) {}
  return 0;
}
