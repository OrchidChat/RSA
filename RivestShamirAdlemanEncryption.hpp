//
// Created by lev8j on 24.07.2026.
//

#pragma once
#include <utility>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

using namespace boost::multiprecision;
using namespace boost::random;


class RivestShamirAdlemanEncryption {
public:


    static uint512_t getRandomUint512(){
        uint512_t random;

        std::random_device random_device;
        std::mt19937_64 randomNumberGen(random_device());

        for (int i = 0; i < 8; i++) {
            random <<= 64;
            random += randomNumberGen();
        }

        return random;
    };

    static bool millerRabinTest(const uint512_t &number) {
        const uint512_t decremented = number - 1;

        //With those two you can find the whole list of exponents
        uint512_t smallestExpo = decremented;
        int exponentCounter = 0;


        //if its divisible by 4
        while ((smallestExpo & 1) == 0) {
            smallestExpo /= 2;
            exponentCounter++;
        }

        int k = 25; // fehler quote 1/(4^k)


        const boost::random::uniform_int_distribution<uint512_t> intDistribution(1, decremented);
        std::random_device random_device;
        std::mt19937_64 random(random_device());
        vector<uint1024_t> testNumVec;


        for (int i = 0; i < k; i++) {
            uint1024_t testNumOriginal = intDistribution(random);

            uint1024_t testNum = testNumOriginal;

            testNumVec.clear();




            int512_t smallestExpoCopy = smallestExpo;


            //Calculate the first number in the table
            while (smallestExpoCopy > 0) {
                if ((smallestExpoCopy & 1) == 1) {
                    testNum = (testNum * testNumOriginal) % number;
                    --smallestExpoCopy;
                }

                testNum = (testNum * testNum) % number;

                smallestExpoCopy >>= 1;// /2
            }

            testNumVec.push_back(testNum);


            //Testing if it's -1 or 1 if so we break and don't need to continue for this a
            if (testNum == decremented || testNum == 1) {

                cout << testNumVec.at(0) << endl;
                continue;
            }

            int exponentCounterCopy = exponentCounter;


            while (exponentCounterCopy > 0) {
                exponentCounterCopy--;

                testNum = (testNum * testNum) % number;

                testNumVec.push_back(testNum);

                // -1 in last column
                if (exponentCounter == 0) {
                    return false;
                }


                //-1 in not last column so we stop check for this column
                if (testNum == decremented) {
                    break;
                }

                //gets caught if it's 1 without a -1 before so return false
                if (testNum == 1) return false;


            }

            cout << testNumOriginal << endl;

            for ( const uint1024_t &testNumIter : testNumVec ) {
                cout << testNumIter << " ";
            }

            cout << endl;

            if (testNum != 1) return false;





        }

        //All the checks were true so we return true

        return true;
    };

    static uint512_t choseRandomPrime() {
        uint512_t random = getRandomUint512();
        random <<= 1;
        --random;

        while (!millerRabinTest(random)) {
            random = getRandomUint512();
            random <<= 1;
            --random;
        }

        return random;
    };

    static std::pair<uint512_t, uint512_t> createKeys(){
        uint512_t num1 = 1;
        uint512_t num2 = 1;
        return std::make_pair(num1, num2);
    };




};
