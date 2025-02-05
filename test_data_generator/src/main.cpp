#include "include/ccsds.hpp"
#include "include/fec.hpp"
#include "include/crc.hpp"
#include <cstring>
#include <cstdio>
#include <fstream>
using namespace std;

#define MAX_TX_FRAME_LEN 1024
#define TX_FRAME_LEN 223
#define SYNC_WORD 0x3C674952
#define POSTAMBLE_BYTES 8


int main(void) {
	struct tx_frame {
            uint16_t len;
            uint32_t timeout_ms;
            uint8_t pdu[MAX_TX_FRAME_LEN];
        };

        struct tx_frame msg{};

	msg.len = 0;
	memset(msg.pdu, 0, TX_FRAME_LEN);
        msg.pdu[msg.len++] = 'h';
        msg.pdu[msg.len++] = 'e';
        msg.pdu[msg.len++] = 'l';
        msg.pdu[msg.len++] = 'l';
        msg.pdu[msg.len++] = 'o';
        msg.pdu[msg.len++] = ' ';
        msg.pdu[msg.len++] = 'w';
        msg.pdu[msg.len++] = 'o';
        msg.pdu[msg.len++] = 'r';
        msg.pdu[msg.len++] = 'l';
        msg.pdu[msg.len++] = 'd';

	msg.len = TX_FRAME_LEN;


        struct tx_frame tmp_tx_msg{};

        /* Calculate and append CRC for all encodings */
        /*uint32_t c = crc32_c(msg.pdu, msg.len);
        msg.pdu[msg.len] = c >> 24;
        msg.pdu[msg.len + 1] = c >> 16;
        msg.pdu[msg.len + 2] = c >> 8;
        msg.pdu[msg.len + 3] = c;
        msg.len += sizeof(uint32_t);*/

        /* Always perform CCSDS scrambling */
        ccsds_scrambler(msg.pdu, msg.len);

        memset(tmp_tx_msg.pdu, 0x33, 8);
        tmp_tx_msg.len = 8;
        tmp_tx_msg.pdu[tmp_tx_msg.len++] = static_cast<uint8_t>(SYNC_WORD >> 24);
        tmp_tx_msg.pdu[tmp_tx_msg.len++] = static_cast<uint8_t>(SYNC_WORD >> 16);
        tmp_tx_msg.pdu[tmp_tx_msg.len++] = static_cast<uint8_t>(SYNC_WORD >> 8);
        tmp_tx_msg.pdu[tmp_tx_msg.len++] = static_cast<uint8_t>(SYNC_WORD);

        memcpy(tmp_tx_msg.pdu + tmp_tx_msg.len, msg.pdu, msg.len);
        tmp_tx_msg.len += msg.len;

        /* Perform RS */
        rs_encode(tmp_tx_msg.pdu + tmp_tx_msg.len,
                msg.pdu, msg.len);
        tmp_tx_msg.len += 32;

	ofstream myfile;
	myfile.open ("data_no_cc.bin");

	char test[1] = {0};

	for (int i=0; i<tmp_tx_msg.len; i++) {
		for (int ii=7; ii>=0; ii--) {
			if (((tmp_tx_msg.pdu[i] >> ii) & 0b00000001) == 0b00000001) test[0]=1;
			else test[0]=0;
			myfile.write(test,1);
		}
		//printf("%02x ", tmp_tx_msg.pdu[i]);
	}
	test[0] = 0;
	for (int i=0; i<512; i++) myfile.write(test,1);
	myfile.flush();
	myfile.close();
	//printf("\n\n");
        /*
         * Append a zero byte (more than 6 zero bits), to ensure
         * the reset of the convolutional encoder
         */
        tmp_tx_msg.pdu[tmp_tx_msg.len++] = 0;
        conv_encoder_1_2_7(msg.pdu, tmp_tx_msg.pdu,
                tmp_tx_msg.len);
        /* For consistency copy back the result */
        memcpy(tmp_tx_msg.pdu, msg.pdu, 2 * tmp_tx_msg.len);
        tmp_tx_msg.len *= 2;
        tmp_tx_msg.len += POSTAMBLE_BYTES;

	myfile.open ("data_cc.bin");
	test[0] = 0;
	for (int i=0; i<512; i++) myfile.write(test,1);
	for (int i=0; i<tmp_tx_msg.len; i++) {
		for (int ii=7; ii>=0; ii--) {
			if (((tmp_tx_msg.pdu[i] >> ii) & 0b00000001) == 0b00000001) test[0]=1;
			else test[0]=0;
			myfile.write(test,1);
		}
		//printf("%02x ", tmp_tx_msg.pdu[i]);
	}
	test[0] = 0;
	for (int i=0; i<512; i++) myfile.write(test,1);
	myfile.flush();
	myfile.close();

	return 0;
}
