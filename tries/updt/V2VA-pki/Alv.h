/**
 * Protocol definition:
 * B0 = FE (msg start)
 * B1 = sequence number (each side has different sequence number)
 * B2 = length
 * B3 = opcode
 * B4 - Bn-2 = Data
 * Bn-1 - Bn = CRC
 * @brief ALV (Autonomous Land Vehicle) Protocol
 * @authors Alex Stoliar (alexstolr@gmail.com); Mohammad Najjar (najjar@post.bgu.ac.il)
 * @date 23/09/16
 */


#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/rabin.h>

#ifndef V2VA_ALV_H
#define V2VA_ALV_H


#include <stdint.h>

class Alv {

public:
    Alv();
    ~Alv();

private:
    void init();
    void randRSA();

    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::RSA::PrivateKey privKey;
    CryptoPP::RSA::PublicKey pubKeySrc;
    std::string ca;

    CryptoPP::RSA::PublicKey pubKeyDst;




    /*
    uint64_t pubKeySrc;
    uint64_t certSrc;
    int seqNumSrc;
    uint64_t pubKeyDst;

    uint64_t certDst;
    int seqNumDst;
     */
    void msgPack();

    void msgUnpack(char * msg);


};


#endif //V2VA_ALV_H
