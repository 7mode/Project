//
// Created by alex on 25/09/16.
//

#include "crc32.h"
#include <stdio.h>
#include <inttypes.h>
#include <iostream>
#include <sstream>

crc32::crc32() {

}

uint32_t crc32::calcCrc(char *buf) {

    int i;
    uint32_t crc = 0;
    char * buffer = "hello";
    int len = 5;


    for (i = 0; i < len; i++) {
        crc = crc32_tab[(crc ^ buffer[i]) & 0xFF] ^ (crc >> 8);
    }
    printf("%" PRIu32 "\n",crc ^ 0xFFFFFFFFUL);
    //printf("%d \n",crc ^ 0xFFFFFFFFUL);
    return crc ^ 0xFFFFFFFFUL;


/*
int i, j;
int byte;
unsigned int crc, mask;
for (byte = 0; byte <= 255; byte++) {
    crc = byte;
    for (j = 7; j >= 0; j--) {    // Do eight times.
        mask = -(crc & 1);
        crc = (crc >> 1) ^ (0xEDB88320 & mask);
    }
    crc32_tab[byte] = crc;




    i = 0;
    crc = 0xFFFFFFFF;
    while ((byte = buf[i]) != 0) {
        crc = (crc >> 8) ^ crc32_tab[(crc ^ byte) & 0xFF];
        i = i + 1;
    }
    return ~crc;
}
 */
}



/*

    @Author: Alex Stoliar

    calculates crc32 on for 11 bytes starting at address of iArr + 1

    @param: iArr - address of array of bytes representing the message sent to pedistal


 */
/*
quint32 Crc32::calculateFromArray(int * iArr){

    quint32 crc;

    int i, len = 11; // 12'th digit is crc

    crc = 0xFFFFFFFFUL; // Maximal value which can be stored in an unsigned int variable.

    for (i = 1; i <= len; i++)

    {   if (DEBUG)

            printf("iArr[%d] = %0x\n",i,iArr[i]);

        crc = crc_table[(crc ^ iArr[i]) & 0xFF] ^ (crc >> 8);

    }

    return crc ^ 0xFFFFFFFFUL;

}*/