//
// Created by lev8j on 24.07.2026.
//
#include <iostream>
#include <random>
using namespace std;
#include "boost/multiprecision/cpp_int.hpp"
#include "RivestShamirAdlemanEncryption.hpp"

using namespace boost::multiprecision;



int main() {


    // vector<uint512_t> testArr;
    //
    // for (int i = 5; i < 2000; i += 2) {
    //     testArr.emplace_back(i);
    // }
    //
    //
    // for (const auto & i : testArr) {
    //     cout << i << ": ";
    //     if (RivestShamirAdlemanEncryption::millerRabinTest(i)) cout << "True";
    //     else cout << "False";
    //
    //     cout << endl;
    // }


    // for (int i = 0; i < 10; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         break;
    //         cout <<j<< endl;
    //     }
    //
    //     cout << i <<endl;
    // }
    //
    // cout << "finish" << endl;


    const uint512_t test = 7;

    if (RivestShamirAdlemanEncryption::millerRabinTest(test)) {
        cout<< "True";
    }
    else {
        cout<< "False";
    }

    cout << endl;


     return 0;


}



