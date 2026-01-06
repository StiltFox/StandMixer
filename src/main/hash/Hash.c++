/*******************************************************
* Created by Cryos on 5/24/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "Hash.h++"
#include "DataConverter.h++"
#include <array>
#include <queue>
#include <iostream>
#include <cstdint>
#include <climits>

using namespace std;
using namespace StiltFox::StandMixer;

const array<uint64_t, 8> DEFAULT_HASH_VALUES =
    {
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1, 0x510e527fade682d1,
        0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    };

const array<uint32_t, 64> CONSTANTS =
    {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98,
        0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
        0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8,
        0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
        0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
        0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
        0xc67178f2
    };

uint32_t getNextWord(const string& bytes, size_t& index)
{
    uint32_t output = 0x00000000;
    size_t i = 0;

    for (i = 0; index + i < bytes.size() && i < 4; i++) output = (output << 8) + bytes[index + i];
    if (i<4)
    {
        output = (output << 8) +0x80;
        i++;
        for (; i < 4; i++) output = output << 8;
    }
    index += 4;

    return output;
}

static uint32_t rotateRight (uint32_t n, unsigned int c)
{
    const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);

    c &= mask;
    return (n>>c) | (n<<( (-c)&mask ));
}

uint32_t calculateNextLine(vector<uint32_t>& currentMessageBlock)
{
    const uint32_t w0 = currentMessageBlock[currentMessageBlock.size() - 16];
    const uint32_t w1 = currentMessageBlock[currentMessageBlock.size() - 15];
    const uint32_t w9 = currentMessageBlock[currentMessageBlock.size() - 7];
    const uint32_t w14 = currentMessageBlock[currentMessageBlock.size() - 2];

    const uint32_t theta0 = rotateRight(w1, 7) ^ rotateRight(w1, 18) ^ (w1 >> 3);
    const uint32_t theta1 = rotateRight(w14, 17) ^ rotateRight(w14, 19) ^ (w14 >> 10);

    return w0 + theta0 + w9 + theta1;
}

void updateWorkingVariables(uint32_t word, vector<uint32_t>& workingVariables, size_t& currentConstant)
{
    uint32_t majority = (workingVariables[0] & workingVariables[1]) ^ (workingVariables[0] & workingVariables[2]) ^
        (workingVariables[1] & workingVariables[2]);
    uint32_t sum0 = rotateRight(workingVariables[0], 2) ^ rotateRight(workingVariables[0], 13) ^
        rotateRight(workingVariables[0], 22);
    uint32_t choice = (workingVariables[4] & workingVariables[5]) ^ ((~workingVariables[4]) & workingVariables[6]);
    uint32_t sum1 = rotateRight(workingVariables[4], 6) ^ rotateRight(workingVariables[4], 11) ^
        rotateRight(workingVariables[4], 25);
    uint32_t temp2 = sum0 + majority;
    uint32_t temp1 = workingVariables[7] + sum1 + choice + word + CONSTANTS[currentConstant];

    workingVariables[7] = workingVariables[6];
    workingVariables[6] = workingVariables[5];
    workingVariables[5] = workingVariables[4];
    workingVariables[4] = workingVariables[3] + temp1;
    workingVariables[3] = workingVariables[2];
    workingVariables[2] = workingVariables[1];
    workingVariables[1] = workingVariables[0];
    workingVariables[0] = temp1 + temp2;
    currentConstant++;
}

void processMessageSchedule(vector<uint32_t>& messageSchedule, vector<uint32_t>& workingVariables,
    vector<uint32_t>& output, size_t& constantIndex)
{
    do
    {
        uint32_t nextLine = calculateNextLine(messageSchedule);
        updateWorkingVariables(nextLine, workingVariables, constantIndex);
        messageSchedule.erase(messageSchedule.begin());
        messageSchedule.emplace_back(nextLine);
    } while (constantIndex < 64);

    messageSchedule.clear();

    output[0] += workingVariables[0];
    output[1] += workingVariables[1];
    output[2] += workingVariables[2];
    output[3] += workingVariables[3];
    output[4] += workingVariables[4];
    output[5] += workingVariables[5];
    output[6] += workingVariables[6];
    output[7] += workingVariables[7];

    workingVariables[0] = output[0];
    workingVariables[1] = output[1];
    workingVariables[2] = output[2];
    workingVariables[3] = output[3];
    workingVariables[4] = output[4];
    workingVariables[5] = output[5];
    workingVariables[6] = output[6];
    workingVariables[7] = output[7];
    constantIndex = 0;
}

vector<uint32_t> calculateSha256(const string& input)
{
    vector<uint32_t> output = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab,
                             0x5be0cd19};
    vector<uint32_t> workingVariables = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c,
                             0x1f83d9ab, 0x5be0cd19};
    vector<uint32_t> messageSchedule;
    size_t padding, constantIndex = 0, currentIndex = 0;
    uint64_t byteSize = input.size() * 8;
    if (padding = 64 - ((input.size() + 9) % 64); padding >= 64) padding = 0;
    padding = padding / 4;

    while (currentIndex < input.size())
    {
        uint32_t word = getNextWord(input, currentIndex);
        updateWorkingVariables(word, workingVariables, constantIndex);
        messageSchedule.emplace_back(word);
        if (messageSchedule.size() >= 16)
            processMessageSchedule(messageSchedule, workingVariables, output, currentIndex);
    }

    for (int x = 0; x < padding; x++)
    {
        updateWorkingVariables(0x00000000, workingVariables, constantIndex);
        messageSchedule.emplace_back(0x00000000);
    }

    updateWorkingVariables((byteSize & 0xffffffff00000000) >> 32, workingVariables, constantIndex);
    messageSchedule.emplace_back((byteSize & 0xffffffff00000000) >> 32);
    updateWorkingVariables(byteSize & 0x00000000ffffffff, workingVariables, constantIndex);
    messageSchedule.emplace_back(byteSize & 0x00000000ffffffff);
    processMessageSchedule(messageSchedule, workingVariables, output, constantIndex);

    return output;
}

string Hash::sha256(const string& data)
{
    auto shaNumericValue = calculateSha256(data);
    return DataConverter::convertDataToHexString(shaNumericValue);
}
//
// string Hash::sha512(string data)
// {
//     return encrypt(data, CryptoPP::SHA512());
// }
//
// string Hash::md5(string data)
// {
//     return encrypt(data, CryptoPP::Weak1::MD5());
// }