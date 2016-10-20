/**
 * @brief ALV (Autonomous Land Vehicle) Protocol
 * @authors Alex Stoliar (alexstolr@gmail.com); Mohammad Najjar (najjar@post.bgu.ac.il)
 * @date 23/09/16
 */

#include "Alv.h"

/**
 * @brief default constructor
 * @return
 */
Alv::Alv()
{

}

void Alv::init()
{
    privKey.GenerateRandomWithKeySize(prng, 64);
    CryptoPP::RSA::PublicKey tmp(privKey);
    pubKeySrc = tmp;

    CryptoPP::SHA256 hash;
    byte digest[CryptoPP::SHA256::DIGESTSIZE];
    //std::string str;
    //std::cout << "Enter a string: ";
    // std::getline(std::cin, str);

//    RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Signer signer;
//    RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Verifier verifier;

    hash.CalculateDigest(digest, (const byte *) pubKeySrc, str.size());

    CryptoPP::HexEncoder encoder;
    CryptoPP::StringSink *SS = new CryptoPP::StringSink(output);
    encoder.Attach(SS);
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
}

/*
void randRSA()
{

    //mnualRSA();

    // rand
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::RSA::PrivateKey privKey;

    privKey.GenerateRandomWithKeySize(prng, 64);

    // generate public key
    CryptoPP::RSA::PublicKey pubKey(privKey);

    std::string message = "secret", recovered;
    CryptoPP::Integer m((const byte *)message.data(), message.size());
    std::cout << "m: " << std::hex << m << std::endl;

    //encrypt
    CryptoPP::Integer c = pubKey.ApplyFunction(m);
    std::cout << "c: " << std::hex << c << std::endl;

    //decrypt
    CryptoPP::Integer r = privKey.CalculateInverse(prng, c);
    std::cout << "r: " << std::hex << r << std::endl;

    //recover
    size_t req = r.MinEncodedSize();
    recovered.resize(req);

    r.Encode((byte *)recovered.data(), recovered.size());
    std::cout << "recovered: " << recovered << std::endl;
}*/