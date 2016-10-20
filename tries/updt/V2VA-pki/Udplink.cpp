/**
 * @brief connection via UDP.
 * @authors Alex Stoliar (alexstolr@gmail.com); Mohammad Najjar (najjar@post.bgu.ac.il)
 * @date 23/09/16
 */
//see this for reference: http://stackoverflow.com/questions/12515005/receiving-udp-broadcast
//                        http://www.linuxhowtos.org/C_C++/socket.htm
#include "Udplink.h"
#include <stdio.h>
#include <string.h>
#include  <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


Udplink::Udplink()
{
    udpSoc = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    memset(&locAddr, 0, sizeof(locAddr));
    locAddr.sin_family = AF_INET;
    locAddr.sin_addr.s_addr = inet_addr("10.56.3.240");//INADDR_ANY;
    locAddr.sin_port = htons(UDP_LOCAL_PORT);

    if (bind(udpSoc,(struct sockaddr *)&locAddr, sizeof(struct sockaddr)) == 0)
    {
        printf("binding local address succesful!\n");
        memset(&dstAddr, 0, sizeof(dstAddr));
        dstAddr.sin_family = AF_INET;
        dstAddr.sin_addr.s_addr = inet_addr("10.56.3.243"); //target ip 192.168.56.1    10.56.3.241
        dstAddr.sin_port = htons(UDP_DEST_PORT);
    }
    else
    {
        perror("error bind failed\n");
    }
}

int Udplink::writeDatagram(char * datagram) {
    return sendto(udpSoc, datagram,strlen(datagram), 0, (struct sockaddr*)&dstAddr, sizeof(struct sockaddr_in)); //locAddr
}

int Udplink::readDatagram() {
    char dataGram[256];
    unsigned slen=sizeof(sockaddr);
    int bytesRead = recvfrom(udpSoc, dataGram, strlen(dataGram)-1, 0, (sockaddr *)&locAddr, &slen); //dstAddr
    printf("message receive: %s\n", dataGram);
    return bytesRead;
}
