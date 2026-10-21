//
// Created by lev8j on 30.09.2026.
//

#include "RivestShamirAdlemanEncryption.hpp"
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;


int main() {
    auto keys = RivestShamirAdlemanEncryption::createModuleAndKeys();
    uint512_t publicKey = keys.second.first;
    uint1024_t privateKey = keys.second.second;
    uint1024_t module = keys.first;

    // uint512_t publicKey = 5;
    // uint1024_t phi = 756;
    // uint1024_t privateKey = 605;
    // uint1024_t module = 817;

    std::cout << "publicKey: " << publicKey << std::endl;
    std::cout << "privateKey: " << privateKey << std::endl;
    std::cout << "Module: " << module << std::endl;

    std::vector<uint8_t> message;
    message.push_back('S');
    std::cout << "raw: " << message[0] << "\n\n" << std::endl;

    std::vector<uint8_t> encryptedMessage = RivestShamirAdlemanEncryption::encrypt(message, publicKey, module);

    std::cout << "encrypted: ";

    for (int i = encryptedMessage.size()-1; i >= 0; i--) {
        std::cout << static_cast<unsigned int>(encryptedMessage[i]) << " ";
    }

    std::cout << std::endl;
    std::cout << "\n\ndecrypted: " << std::endl;

    std::vector<uint8_t> decryptedMessage = RivestShamirAdlemanEncryption::decrypt(encryptedMessage, privateKey, module);

    std::cout << decryptedMessage[0] << std::endl;

    // uint1024_t privateKey = RivestShamirAdlemanEncryption::getPrivateKey(publicKey, phi);
    // std::cout << "Private Key: " << privateKey << std::endl;

    //std::cout << RivestShamirAdlemanEncryption::choseRandomPrime() << std::endl;
    return 0;
}
