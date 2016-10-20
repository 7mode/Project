/**
 * @brief connection via UDP.
 * @authors Alex Stoliar (alexstolr@gmail.com); Mohammad Najjar (najjar@post.bgu.ac.il)
 * @date 23/09/16
 */

#ifndef V2VA_UDPLINK_H
#define V2VA_UDPLINK_H


#include <sys/socket.h>
#include <netinet/in.h> //  sockaddr_in

#define UDP_LOCAL_PORT 16008
#define UDP_DEST_PORT 16007
#define BUF_SIZE 1024

class Udplink {
public:
    Udplink();
    int readDatagram();
    int writeDatagram(char * dg);

private:
    int udpSoc; //  udp socket file descriptor
    int broadcast = 1;
    struct sockaddr_in locAddr, dstAddr;
    char buffer[BUF_SIZE] = {0};   //Stores received data. Initiated to 0's


};


#endif //V2VA_UDPLINK_H
