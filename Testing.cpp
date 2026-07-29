//
// Created by lev8j on 24.07.2026.
//
#include <iostream>
#include <random>
using namespace std;
#include "boost/multiprecision/cpp_int.hpp"
#include "RivestShamirAdlemanEncryption.hpp"

using namespace boost::multiprecision;

void testExpo() {
    int testNum = 1;
    int testNumOriginal = 2;
    int smallestExpoCopy = 5;
    int number = 11;

    while (smallestExpoCopy > 0) {

        if ((smallestExpoCopy & 1) == 1) {
            testNum = (testNum * testNumOriginal) % number;
        }

        testNumOriginal = (testNumOriginal * testNumOriginal) % number;

        smallestExpoCopy >>= 1;
    }


    cout << testNum << endl;
}

int main() {


    // vector<uint512_t> testArr;
    //
    // for (int i = 5; i < 10000; i += 2) {
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


    // const uint512_t test("85053461164796801949539541639542805770666392330682673302530819774105141531698707146930307290253537320447270457");
    //
    // if (RivestShamirAdlemanEncryption::millerRabinTest(test)) {
    //     cout<< "True";
    // }
    // else {
    //     cout<< "False";
    // }
    //
    // cout << endl;

    cout<< RivestShamirAdlemanEncryption::choseRandomPrime() << endl;


    // testExpo();

     return 0;


}






