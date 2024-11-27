#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t msg_id; /* 2-bit */
    uint8_t seq_num;  /* 4-bit */
    uint8_t fname_seq;  /* 6-bit */
    uint8_t errcode; /* 4-bit */
} message_t;

message_t msg;

uint8_t chopBit(uint16_t packet, int pos, int len) {
    uint8_t mask = -1; //.  111111111
    //mask <<= len;   //. 11111 00
    mask = ~(mask << len);     //. 0000. 1111
    printf("mask: %d\n", mask);
    packet >>= pos;
    return packet & mask;
}

// little endian
void process_packet2(uint16_t packet) {
    msg.msg_id = chopBit(packet, 0, 2);
    msg.seq_num = chopBit(packet, 2, 4);
    msg.fname_seq = chopBit(packet, 6, 6);
    msg.errcode = chopBit(packet, 12, 4);
    printf("Msg ID: %d\n", msg.msg_id);
    printf("Sequence num: %d\n", msg.seq_num);
    printf("fname seq: %d\n", msg.fname_seq);
    printf("Error code: %d\n", msg.errcode);
    
}


// for big endian
void process_packet(uint16_t packet) {
    /*for (int i = 0; i < 16; i++) {
        if (i < 2) {
            msg.msg_id[i] = packet[i];
        } else if (i < 6) {
            msg.seq_num[i] = packet[i];
        } else if (i < 12) {
            msg.fname_seq[i] = packet[i];
        } else {
            msg.errcode[i] = packet[i];
        }
    }*/
    //if (msg.dkk)
}

uint16_t test_case1[] = {0x50E5, 0x8CB3};
    
    
    //0x50E5 /*0101.  000011.   1001      01*/, 
    
   // 0x8CB3 /* 1000.   110010.  1100  11 */};

int main() {
    for (int i = 0; i < 2; i++) {
        process_packet2(test_case1[i]);
    }
    return 0;
}

//bit endian
/*00 0000. 000000  0000
1000110010110011
1000110010110011

msg_id: 2
seq_num: 4
fname_seq: 6
errorcode: 4
*/
