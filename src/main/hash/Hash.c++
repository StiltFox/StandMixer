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

constexpr array<uint64_t, 8> DEFAULT_HASH_VALUES =
    {
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1, 0x510e527fade682d1,
        0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    };

constexpr array<uint64_t, 80> CONSTANTS =
    {
        0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
        0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
        0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
        0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab,
        0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
        0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
        0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
        0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
        0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
        0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
        0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6,
        0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
        0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
    };

uint32_t getDefaultHashValue32Bit(const int index)
{
    return DEFAULT_HASH_VALUES[index] >> 32;
}

uint32_t getConstant32Bit(const int index)
{
    return CONSTANTS[index] >> 32;
}

template <typename T>
T getNextWord(const string& bytes, size_t& index)
{
    T output = 0;
    size_t i = 0;

    for (i = 0; index + i < bytes.size() && i < sizeof(T); i++) output = (output << 8) + bytes[index + i];
    if (i<sizeof(T))
    {
        output = (output << 8) +0x80;
        i++;
        for (; i < sizeof(T); i++) output = output << 8;
    }
    index += sizeof(T);

    return output;
}

template <typename T>
static T rotateRight (T n, unsigned int c)
{
    const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);

    c &= mask;
    return (n>>c) | (n<<( (-c)&mask ));
}

template <typename T>
T calculateNextLine(const vector<T>& currentMessageBlock)
{
    T theta0, theta1;
    const T w0 = currentMessageBlock.at(0);
    const T w1 = currentMessageBlock.at(1);
    const T w9 = currentMessageBlock.at(9);
    const T w14 = currentMessageBlock.at(14);

    if (sizeof(T) < sizeof(uint64_t))
    {
        theta0 = rotateRight(w1, 7) ^ rotateRight(w1, 18) ^ (w1 >> 3);
        theta1 = rotateRight(w14, 17) ^ rotateRight(w14, 19) ^ (w14 >> 10);
    }
    else
    {
        theta0 = rotateRight(w1, 1) ^ rotateRight(w1, 8) ^ (w1 >> 7);
        theta1 = rotateRight(w14, 19) ^ rotateRight(w14, 61) ^ (w14 >> 6);
    }

    return w0 + theta0 + w9 + theta1;
}

template <typename T>
void updateWorkingVariables(vector<T>& workingVariables, T temp1, T temp2, size_t& currentConstant)
{
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

template <typename T>
void calculateWorkingVariables(T word, vector<T>& workingVariables, size_t& currentConstant)
{
    T sum0, sum1, constant;

    if (sizeof(T) < sizeof(uint64_t))
    {
        constant = getConstant32Bit(currentConstant);
        sum0 = rotateRight(workingVariables[0], 2) ^ rotateRight(workingVariables[0], 13) ^
            rotateRight(workingVariables[0], 22);
        sum1 = rotateRight(workingVariables[4], 6) ^ rotateRight(workingVariables[4], 11) ^
            rotateRight(workingVariables[4], 25);
    }
    else
    {
        sum0 = rotateRight(workingVariables[0], 28) ^ rotateRight(workingVariables[0], 34) ^
            rotateRight(workingVariables[0], 39);
        sum1 = rotateRight(workingVariables[4], 14) ^ rotateRight(workingVariables[4], 18) ^
            rotateRight(workingVariables[4], 41);
    }

    T majority = (workingVariables[0] & workingVariables[1]) ^ (workingVariables[0] & workingVariables[2]) ^
        (workingVariables[1] & workingVariables[2]);
    T choice = (workingVariables[4] & workingVariables[5]) ^ ((~workingVariables[4]) & workingVariables[6]);
    T temp2 = sum0 + majority;
    T temp1 = workingVariables[7] + sum1 + choice + word + constant;

    updateWorkingVariables(workingVariables, temp1, temp2, currentConstant);
}

template <typename T>
void processMessageSchedule(vector<T>& messageSchedule, vector<T>& workingVariables, vector<T>& output,
    size_t& constantIndex, size_t numberOfLoops)
{
    do
    {
        T nextLine = calculateNextLine(messageSchedule);
        calculateWorkingVariables(nextLine, workingVariables, constantIndex);
        messageSchedule.erase(messageSchedule.begin());
        messageSchedule.emplace_back(nextLine);
    } while (constantIndex < numberOfLoops); //64 or 80

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

template <typename T>
void initializeVariables(vector <T>& originalHash, vector <T>& workingVariables, size_t& numberOfLoops)
{
    for (int x=0; x < DEFAULT_HASH_VALUES.size(); x++)
    {
        if (sizeof(T) < sizeof(uint64_t))
        {
            originalHash.emplace_back(getDefaultHashValue32Bit(x));
            workingVariables.emplace_back(getDefaultHashValue32Bit(x));
            numberOfLoops = 64;
        }
        else
        {
            originalHash.emplace_back(DEFAULT_HASH_VALUES[x]);
            workingVariables.emplace_back(DEFAULT_HASH_VALUES[x]);
            numberOfLoops = 80;
        }
    }
}

template <typename T>
void addPadding(const string& input, vector<T>& messageSchedule, vector<T>& workingVariables,
    size_t& constantIndex)
{
    size_t padding = 0;

    if (sizeof(T) == sizeof(uint64_t))
    {
        if (padding = 128 - ((input.size() + 17) % 128); padding >= 128) padding = 0;
        padding = padding / 8;
    }
    else
    {
        if (padding = 64 - ((input.size() + 9) % 64); padding >= 64) padding = 0;
        padding = padding / 4;
    }

    for (int x=0; x < padding; x++)
    {
        calculateWorkingVariables((T)0, workingVariables, constantIndex);
        messageSchedule.emplace_back((T)0);
    }
}

template <typename T>
void addMessageSize(uint64_t byteSize, vector<T>& workingVariables, vector<T>& messageSchedule, size_t& constantIndex)
{
    if (sizeof(T) < sizeof(uint64_t))
    {
        calculateWorkingVariables((T)(byteSize & 0xffffffff00000000) >> 32, workingVariables, constantIndex);
        messageSchedule.emplace_back((byteSize & 0xffffffff00000000) >> 32);
        calculateWorkingVariables((T)byteSize & 0x00000000ffffffff, workingVariables, constantIndex);
        messageSchedule.emplace_back(byteSize & 0x00000000ffffffff);
    }
    else
    {
        calculateWorkingVariables((T)0, workingVariables, constantIndex);
        messageSchedule.emplace_back(0);
        calculateWorkingVariables((T)byteSize, workingVariables, constantIndex);
        messageSchedule.emplace_back(byteSize);
    }
}

template <typename T>
vector<T> calculateSha2(const string& input)
{
    vector<T> output, workingVariables, messageSchedule;
    size_t numberOfLoops, constantIndex = 0, currentIndex=0;
    uint64_t byteSize = input.size() * 8;

    initializeVariables(output, workingVariables, numberOfLoops);

    while (currentIndex < input.size())
    {
        auto word = getNextWord<T>(input, currentIndex);
        calculateWorkingVariables(word, workingVariables, constantIndex);
        messageSchedule.emplace_back(word);
        if (messageSchedule.size() >= 16)
            processMessageSchedule(messageSchedule, workingVariables, output, currentIndex, numberOfLoops);
    }

    addPadding(input, messageSchedule, workingVariables, constantIndex);
    addMessageSize(byteSize, workingVariables, messageSchedule, constantIndex);
    processMessageSchedule(messageSchedule, workingVariables, output, constantIndex, numberOfLoops);

    return output;
}

string Hash::sha256(const string& data)
{
    const auto shaNumericValue = calculateSha2<uint32_t>(data);
    return DataConverter::convertDataToHexString(shaNumericValue);
}

string Hash::sha512(const string& data)
{
    const auto shaNumericValue = calculateSha2<uint64_t>(data);
    return DataConverter::convertDataToHexString(shaNumericValue);
}

// string Hash::md5(string data)
// {
//     return encrypt(data, CryptoPP::Weak1::MD5());
// }