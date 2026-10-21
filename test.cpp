//
// Created by lev8j on 30.09.2026.
//

#include "RivestShamirAdlemanEncryption.hpp"
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;


int main() {
    auto keys = RivestShamirAdlemanEncryption::createModuleAndKeys();
    uint512_t publicKey("65537");
    uint1024_t privateKey(
        "27346080692578748321668915549217413613607660654100417161927581964057185062313889531059823979051424736774697445394825431354501648446598629956071713193358399285866440566172082061955926783804485146496050003523430945619705662560441079968374181014954674731048831334562648489301681160066447912558941807283783044945");
    uint1024_t module(
        "50616547302780055603615548291271828621317966963814472831396275854447305262486665862599702999833174879939089628571770392709915399052298540159603238556023666377934802073622689245577762833298619496354505602382256027686684958043126281063289677067318922791991016622880802776685677128827620879717505176290521560311");


    // uint512_t testNumber = 100;
    // std::cout << "unencrypted: " << testNumber << std::endl;
    // auto encrypted = RivestShamirAdlemanEncryption::exponentModulo(testNumber, publicKey, module);
    // std::cout << "encrypted: " << encrypted << std::endl;
    // auto decrypted = RivestShamirAdlemanEncryption::exponentModulo(encrypted, privateKey, module);
    // std::cout << "decrypted: " << decrypted << std::endl;


    // uint512_t publicKey = 5;
    // uint1024_t phi = 756;
    // uint1024_t privateKey = 605;
    // uint1024_t module = 817;

    // std::cout << "publicKey: " << publicKey << std::endl;
    // std::cout << "privateKey: " << privateKey << std::endl;
    // std::cout << "Module: " << module << std::endl;

    std::string message = "hallo welt!";
    std::string test = "lm";
    std::cout << "raw: ";

    for (const uint8_t character: message) std::cout << character;

    std::cout << "\n\n" << std::endl;

    std::string encryptedMessage = RivestShamirAdlemanEncryption::encrypt(message, publicKey, module);

    std::cout << "encrypted: ";

    for (int i = encryptedMessage.size() - 1; i >= 0; i--) {
        std::cout << encryptedMessage[i] << " ";
    }

    std::cout << std::endl;
    std::cout << "\n\ndecrypted: " << std::endl;

    std::string decryptedMessage =
            RivestShamirAdlemanEncryption::decrypt(encryptedMessage, privateKey, module);

    for (const uint8_t character: decryptedMessage) std::cout << character;
    std::cout << std::endl;

    // uint1024_t privateKey = RivestShamirAdlemanEncryption::getPrivateKey(publicKey, phi);
    // std::cout << "Private Key: " << privateKey << std::endl;

    //std::cout << RivestShamirAdlemanEncryption::choseRandomPrime() << std::endl;
    return 0;
}
