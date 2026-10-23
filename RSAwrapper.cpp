//
// Created by lev8j on 22.10.2026.
//


#include <iostream>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include "RivestShamirAdlemanEncryption.hpp"

    std::string createKeys() {
        auto keys = RivestShamirAdlemanEncryption::createModuleAndKeys();
        std::stringstream stream;

        stream << keys.first << " " << keys.second.first << " " << keys.second.second;
        return stream.str();
    }

    std::string encryptMessage(const std::string &message, const std::string &publicKeyStr, const std::string &moduleStr) {
        uint512_t publicKey(publicKeyStr);
        uint1024_t module(moduleStr);
        return RivestShamirAdlemanEncryption::encrypt(message, publicKey, module);
    }

    std::string decryptMessage(const std::string &message, const std::string &privateKeyStr, const std::string &moduleStr) {
        uint1024_t privateKey(privateKeyStr);
        uint1024_t module(moduleStr);
        return RivestShamirAdlemanEncryption::decrypt(message, privateKey, module);
    }

    EMSCRIPTEN_BINDINGS(rsaModule) {
        emscripten::function("createKeys", &createKeys);
        emscripten::function("encryptMessage", &encryptMessage);
        emscripten::function("decryptMessage", &decryptMessage);
    }



