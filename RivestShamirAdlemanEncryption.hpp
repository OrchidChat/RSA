//
// Created by lev8j on 24.07.2026.
//

#pragma once
#include <random>
#include <utility>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

using namespace boost::multiprecision;
using namespace boost::random;


class RivestShamirAdlemanEncryption {
public:

    using uint2048_t = boost::multiprecision::number<
    boost::multiprecision::cpp_int_backend<
        2048, // MinBits: Direkt im Objekt gespeicherte Bits
        2048, // MaxBits: Feste Maximale Bit-Größe
        boost::multiprecision::unsigned_magnitude>
>;
    static uint512_t getRandomUint512() {
        uint512_t random;

        std::random_device random_device;
        std::mt19937_64 randomNumberGen(random_device());

        for (int i = 0; i < 8; i++) {
            random <<= 64;
            random += randomNumberGen();
        }

        return random;
    };


    static std::vector<uint8_t> encrypt(const std::vector<uint8_t> &message, const uint512_t &publicKey,
                                        const uint1024_t &module) {
        std::vector<uint512_t> messageInParts(1);

        int used = 0;
        int currentPart = 0;
        uint512_t temp;
        for (int i = 0; i < message.size(); i++, used += 8) {
            if (used == 512) {
                used = 0;
                currentPart++;
                messageInParts.emplace_back(0);
            }
            temp = message[i];
            temp <<= used;
            messageInParts[currentPart] += temp;
        }

        std::vector<uint1024_t> encryptedMessage(messageInParts.size());

        for (int i = 0; i < messageInParts.size(); i++) {
            encryptedMessage[i] = exponentModulo(messageInParts[i], publicKey, module);
        }

        std::vector<uint8_t> output;
        output.reserve(128 * encryptedMessage.size());

        for (const auto &i: encryptedMessage) {
            export_bits(i, std::back_inserter(output), 8, false);
        }

        return output;
    }


    static std::vector<uint8_t> decrypt(const std::vector<uint8_t> &message, const uint1024_t &publicKey,
                                        const uint1024_t &module) {
        std::vector<uint1024_t> messageInParts(1);

        int used = 0;
        int currentPart = 0;
        uint1024_t temp;
        for (int i = 0; i < message.size(); i++, used += 8) {
            if (used == 1024) {
                used = 0;
                currentPart++;
                messageInParts.emplace_back(0);
            }
            temp = message[i];
            temp <<= used;
            messageInParts[currentPart] += temp;
        }

        std::vector<uint512_t> decryptedMessage(messageInParts.size());

        for (int i = 0; i < messageInParts.size(); i++) {
            decryptedMessage[i] = static_cast<uint512_t>(exponentModulo(messageInParts[i], publicKey, module));
        }

        std::vector<uint8_t> output;
        output.reserve(64 * decryptedMessage.size());

        for (const auto &i: decryptedMessage) {
            export_bits(i, std::back_inserter(output), 8, true);
        }

        return output;
    }


    static uint1024_t exponentModulo(uint2048_t input, uint1024_t exponent, const uint1024_t &modulo) {
        uint2048_t currentState = input;
        input = 1;
        while (exponent > 0) {
            if ((exponent & 1) == 1) {
                input = (input * currentState) % modulo;
            }

            currentState = (currentState * currentState) % modulo;

            exponent >>= 1;
        }

        return static_cast<uint1024_t>(input);
    }

    static bool millerRabinTest(const uint512_t &number) {
        const uint512_t decremented = number - 1;

        //With those two you can find the whole list of exponents
        uint512_t smallestExpo = decremented;
        int exponentCounter = 0;


        //if its divisible by 4
        while (smallestExpo % 2 == 0) {
            smallestExpo /= 2;
            exponentCounter++;
        }

        int k = 25; // fehler quote 1/(4^k)


        const boost::random::uniform_int_distribution<uint512_t> intDistribution(2, decremented);
        std::random_device random_device;
        std::mt19937_64 random(random_device());


        for (int i = 0; i < k; i++) {
            uint1024_t testNumOriginal = intDistribution(random);

            uint1024_t testNum = 1;


            int512_t smallestExpoCopy = smallestExpo;


            //Calculate the first number in the row
            while (smallestExpoCopy > 0) {
                if ((smallestExpoCopy & 1) == 1) {
                    testNum = (testNum * testNumOriginal) % number;
                }

                testNumOriginal = (testNumOriginal * testNumOriginal) % number;

                smallestExpoCopy >>= 1;
            }


            //Testing if it's -1 or 1 if so we break and don't need to continue for this a
            if (testNum == decremented || testNum == 1) {
                continue;
            }

            int exponentCounterCopy = exponentCounter;


            while (exponentCounterCopy > 0) {
                exponentCounterCopy--;

                testNum = (testNum * testNum) % number;

                //Last column and we didn't have -1 yet so
                if (exponentCounter == 0) {
                    return false;
                }


                //-1 in not last column so we stop check for this column
                if (testNum == decremented) {
                    break;
                }

                //gets caught if it's 1 without a -1 before so return false
                if (testNum == 1) {
                    return false;
                }
            }

            if (testNum != 1 && testNum != decremented) return false;
        }

        //All the checks were true so we return true

        return true;
    }

    static uint512_t choseRandomPrime() {
        uint512_t random = getRandomUint512();

        if (random % 2 == 0) random--;


        while (!millerRabinTest(random)) {
            random = getRandomUint512();

            if (random % 2 == 0) random--;
        }

        return random;
    };

    static std::pair<uint1024_t, std::pair<uint512_t, uint1024_t> > createModuleAndKeys() {


        //uint1024 because else the multiplication below overflows
        const uint1024_t prime1 = choseRandomPrime();
        const uint1024_t prime2 = choseRandomPrime();


        //Fits because prime1 and prime2 are just 512bits large at max
        const uint1024_t module = prime1 * prime2;
        const uint1024_t phiModule = (prime1 - 1) * (prime2 - 1);

        //chose e public exponent
        const uint512_t publicKey = (2 << 15) + 1;


        const uint1024_t privateKey = getPrivateKey(uint1024_t(publicKey), phiModule);

        return {module, {publicKey, privateKey}};
    };

    static uint1024_t getPrivateKey(const uint1024_t &publicKey, const uint1024_t &phi) {
        auto res = gcde(phi, publicKey);
        return static_cast<uint1024_t>((res.first % phi + phi) % phi);
    }

    static std::pair<int1024_t, int1024_t> gcde(const uint1024_t &a, const uint1024_t &b) {
        auto res = gcdeInner(a, b);

        return std::pair<int1024_t, int1024_t>((res.second.second == a)
                                                   ? std::make_pair(res.first.first, res.second.first)
                                                   : std::make_pair(res.second.first, res.first.first));
    }

    static std::pair<std::pair<int1024_t, uint1024_t>, std::pair<int1024_t, uint1024_t> > gcdeInner(
        const uint1024_t &a, const uint1024_t &b) {
        uint1024_t r = a % b;
        int1024_t q = a / b;
        if (not(b % r))
            return {{1, a}, {-q, b}};

        auto lastLayer = gcdeInner(b, r);


        if (lastLayer.first.second == r) {
            return {
                {lastLayer.first.first, a},
                {lastLayer.second.first + (-q * lastLayer.first.first), lastLayer.second.second}
            };
        } else {
            return {
                {lastLayer.first.first + (-q * lastLayer.second.first), lastLayer.first.second},
                {lastLayer.second.first, a}
            };
        }
    }
};
