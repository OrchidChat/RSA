//
// Created by lev8j on 30.09.2026.
//

#include "RivestShamirAdlemanEncryption.hpp"
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

int main() {
    auto dings = RivestShamirAdlemanEncryption::gcde(240, 46);

    std::cout << dings.first.first << "&" << dings.first.second << "  " << dings.second.first << "&" << dings.second.
            second << std::endl;


    std:: cout << RivestShamirAdlemanEncryption::findPrivateKey(240, 46) << std::endl;

    return 0;
}
