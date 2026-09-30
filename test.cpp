//
// Created by lev8j on 30.09.2026.
//

#include "RivestShamirAdlemanEncryption.hpp"
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;


void printSafe(const std::string& str) {
    for (unsigned char c : str) {
        if (std::isprint(c)) {
            // Normale druckbare Zeichen direkt ausgeben
            std::cout << c;
        } else {
            // Steuerzeichen als \xHEX ausgeben (z. B. \x0A für \n)
            std::cout << "\\x"
                      << std::hex << std::uppercase
                      << std::setw(2) << std::setfill('0')
                      << static_cast<int>(c);
        }
    }

    std::cout << std::endl;
}

int main() {
    auto keys = RivestShamirAdlemanEncryption::createModuleAndKeys();
    uint512_t publicKey = keys.second.first;
    uint1024_t privateKey = keys.second.second;
    uint1024_t module = keys.first;

    std::string message = "Hallo Welt!";

    std::string encryptedMessage = RivestShamirAdlemanEncryption::encrypt(message, publicKey, module);

    printSafe(encryptedMessage);

    std::string decryptedMessage = RivestShamirAdlemanEncryption::decrypt(encryptedMessage, privateKey, module);

    std::cout << decryptedMessage << std::endl;


    return 0;
}
