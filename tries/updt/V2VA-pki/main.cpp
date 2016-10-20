#include "v2va.h"
#include "Udplink.h"
#include "Alv.h"
#include "crc32.h"



#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <thread>


#define OPENALPRCONF "/home/alex/Workspace/OpenALPR/openalpr/src/config/openalpr.conf" //TODO
//http://stackoverflow.com/questions/17291995/push-existing-project-into-github


// Function Declarations
void printWorkingDIr();
void runUdpRead(Udplink * ulink);
void runUdpWrite(Udplink * ulink,char * msg);
void runProtocol(Alv * protocol);

//---------------------------------------------------------
/**
 * @brief main
 * @return
 */
int main() {
    //printWorkingDIr();
    //crc32 c;
    //c.calcCrc("hello");
    //printf("\n");

    //v2va v;
    Alv * protocol = new Alv();
    char * imagePaths [6];
    //std::string partialPath = "/home/alex/Workspace/V2VA/include/Images/";
    //std::string imgPath;
    Udplink * ulink = new Udplink();
    char * data = "hello from alex";
    std::thread t1(runUdpRead,ulink);
    std::thread t2(runUdpWrite,ulink,data);
    std::thread tALV(runProtocol, protocol);

    t1.detach();
    t2.detach();
    while(true)
    {
        sleep(1000);
    }


    //for(int i = 1 ;  i <= 6 ; i++)
    //{

    //while(true){
        //}
        //imgPath = partialPath + std::to_string(i) + ".jpg";
        //std::cout << imgPath << std::endl;
        //imagePaths[i] = (char *)&imgPath;
        //v.imgALPR(imgPath);

    //}


    //v.runOpenALPR();
    //v.runCamera();
    //v.streamALPR();
    delete ulink;
    return 0;
}

//--------------------------------------------------------

/**
 * @brief prints Working Directory
 */
void printWorkingDIr()
{
    char szTmp[32];
    printf("build dir: ");
    sprintf(szTmp, "/proc/%d/exe", getpid());
}


void runUdpRead(Udplink * ulink)
{
    while(true)
    {
        //std::cout << "reading data from " << std::this_thread::get_id() << std::endl;
        ulink->readDatagram();
        sleep(1);
    }

}

void runUdpWrite(Udplink * ulink,char * msg)
{
    while(true)
    {
        //std::cout << "writing data to " << std::this_thread::get_id() << std::endl;
        std::cout << "writing data " << std::endl;
        ulink->writeDatagram(msg);
        sleep(1);
    }
}

void runProtocol(Alv * protocol)
{
    v2va v;
    std::string imgPath = "/home/alex/Workspace/V2VA/include/Images/1.jpg";

}

//------------------------------------------------------------------------

#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/rabin.h>

using namespace CryptoPP;

/*
 * **************** using sha256 ********************
 */

void sha256Test() {
    CryptoPP::SHA256 hash;
    byte digest[CryptoPP::SHA256::DIGESTSIZE];
    std::string str, output;
    std::cout << "Enter a string: ";
    std::getline(std::cin, str);

    RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Signer signer;
    RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Verifier verifier;

    hash.CalculateDigest(digest, (const byte *) str.c_str(), str.size());

    CryptoPP::HexEncoder encoder;
    CryptoPP::StringSink *SS = new CryptoPP::StringSink(output);
    encoder.Attach(SS);
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    std::cout << "The encrypted string is => " << output << std::endl;

    /*
     SHA256 hash;
    string message = "abcdefghijklmnopqrstuvwxyz";
    string digest;

    StringSource s(message, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));

    cout << digest << endl;
     */
}

/*
 * *************** using rsa ******************
 */

void randRSA() {

    //mnualRSA();

    // rand
    AutoSeededRandomPool prng; //Randomly Generated Number
    RSA::PrivateKey privKey;

    privKey.GenerateRandomWithKeySize(prng, 64);

    // generate public key
    RSA::PublicKey pubKey(privKey);

    std::string message = "secret", recovered;
    Integer m((const byte *)message.data(), message.size());
    std::cout << "m: " << std::hex << m << std::endl;

    //encrypt
    Integer c = pubKey.ApplyFunction(m);
    std::cout << "c: " << std::hex << c << std::endl;

    //decrypt
    Integer r = privKey.CalculateInverse(prng, c);
    std::cout << "r: " << std::hex << r << std::endl;

    //recover
    size_t req = r.MinEncodedSize();
    recovered.resize(req);

    r.Encode((byte *)recovered.data(), recovered.size());
    std::cout << "recovered: " << recovered << std::endl;
}

// there are multiple ways to initial the keys!! worth reading rsa.h
void mnualConfigureRSA() {
    Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9");

    RSA::PrivateKey privKey;
    RSA::PublicKey pubKey;

    privKey.Initialize(n, d, e);

    pubKey.Initialize(n, d);
}

/*
 * ************ using rabin encryption ***************
 * it is alternative to rsa - maybe better
 * */
void rabin(){
    AutoSeededRandomPool prng;

    Rabin::PrivateKey privKey;
    privKey.GenerateRandomWithKeySize(prng, 128);
    Rabin::PublicKey pubKey(privKey);

    std::string message, recovered;
    Integer m, c, r;

    message = "secret";
    std::cout << "message: " << message << std::endl;

// Treat the message as a big endian array
    m = Integer((const byte *) message.data(), message.size());
    std::cout << "m: " << std::hex << m << std::endl;

// Encrypt
    c = pubKey.ApplyFunction(m);
    std::cout << "c: " << std::hex << c << std::endl;

// Decrypt
    r = privKey.CalculateInverse(prng, c);
    std::cout << "r: " << std::hex << r << std::endl;

// Round trip it
    size_t req = r.MinEncodedSize();
    recovered.resize(req);
    r.Encode((byte *) recovered.data(), recovered.size());

    std::cout << "recovered: " << recovered << std::endl;

}
