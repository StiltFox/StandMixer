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
#include <functional>
#include <cstdint>
#include <bit>

using namespace std;
using namespace StiltFox::StandMixer;

constexpr array<uint32_t, 64> MD5_CONSTANTS =
    {
        0xD76AA478,0xE8C7B756,0x242070DB,0xC1BDCEEE,0xF57C0FA,0x4787C62A,0xA8304613,0xFD469501,0x698098D8,0x8B44F7AF,
        0xFFFF5BB1,0x895CD7BE,0x6B901122,0xFD987193,0xA679438E,0x49B40821,0xF61E2562,0xC040B340,0x265E5A51,0xE9B6C7AA,
        0xD62F105D,0x02441453,0xD8A1E681,0xE7D3FBC8,0x21E1CDE6,0xC33707D6,0xF4D50D87,0x455A14ED,0xA9E3E905,0xFCEFA3F8,
        0x676F02D9,0x8D2A4C8A,0xFFFA3942,0x8771F681,0x699D6122,0xFDE5380C,0x4BEEA44,0x4BDECFA9,0xF6BB4B60,0xBEBFBC70,
        0x289B7EC6,0xEAA127FA,0xD4EF3085,0x04881D05,0xD9D4D039,0xE6DB99E5,0x1FA27CF8,0xC4AC5665,0xF4292244,0x432AFF97,
        0xAB9423A7,0xFC93A039,0x655B59C3,0x8F0CCC92,0xFFEFF47D,0x85845DD1,0x6FA87E4F,0xFE2CE6E0,0xA3014314,0x4E0811A1,
        0xF7537E82,0xBD3AF235,0x2AD7D2BB,0xEB86D391
    };

constexpr array<unsigned char,64> MD5_ROTATE =
    {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        4, 11, 16, 13, 4, 11, 16, 13, 4, 11, 16, 13, 4, 11, 16, 13,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };


constexpr array<unsigned char, 64> MD5_FEED_ORDER =
    {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
        5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
        0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9
    };

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

uint32_t getDefaultHashValue32Bit(const size_t index)
{
    return DEFAULT_HASH_VALUES[index] >> 32;
}

uint32_t getConstant32Bit(const size_t index)
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
T calculateNextLine(const vector<T>& currentMessageBlock)
{
    T theta0, theta1;
    const T w0 = currentMessageBlock.at(0);
    const T w1 = currentMessageBlock.at(1);
    const T w9 = currentMessageBlock.at(9);
    const T w14 = currentMessageBlock.at(14);

    if (sizeof(T) < sizeof(uint64_t))
    {
        theta0 = rotr(w1, 7) ^ rotr(w1, 18) ^ w1 >> 3;
        theta1 = rotr(w14, 17) ^ rotr(w14, 19) ^ w14 >> 10;
    }
    else
    {
        theta0 = rotr(w1, 1) ^ rotr(w1, 8) ^ w1 >> 7;
        theta1 = rotr(w14, 19) ^ rotr(w14, 61) ^ w14 >> 6;
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
        sum0 = rotr(workingVariables[0], 2) ^ rotr(workingVariables[0], 13) ^
            rotr(workingVariables[0], 22);
        sum1 = rotr(workingVariables[4], 6) ^ rotr(workingVariables[4], 11) ^
            rotr(workingVariables[4], 25);
    }
    else
    {
        constant = CONSTANTS[currentConstant];
        sum0 = rotr(workingVariables[0], 28) ^ rotr(workingVariables[0], 34) ^
            rotr(workingVariables[0], 39);
        sum1 = rotr(workingVariables[4], 14) ^ rotr(workingVariables[4], 18) ^
            rotr(workingVariables[4], 41);
    }

    T majority = workingVariables[0] & workingVariables[1] ^ workingVariables[0] & workingVariables[2] ^
        workingVariables[1] & workingVariables[2];
    T choice = workingVariables[4] & workingVariables[5] ^ ~workingVariables[4] & workingVariables[6];
    T temp2 = sum0 + majority;
    T temp1 = workingVariables[7] + sum1 + choice + word + constant;

    updateWorkingVariables(workingVariables, temp1, temp2, currentConstant);
}

template <typename T>
void processMessageSchedule(vector<T>& messageSchedule, vector<T>& workingVariables, vector<T>& output,
    size_t& constantIndex, const size_t numberOfLoops)
{
    do
    {
        T nextLine = calculateNextLine(messageSchedule);
        calculateWorkingVariables(nextLine, workingVariables, constantIndex);
        messageSchedule.erase(messageSchedule.begin());
        messageSchedule.emplace_back(nextLine);
    } while (constantIndex < numberOfLoops);

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
        if (padding = 128 - (input.size() + 17) % 128; padding >= 128) padding = 0;
        padding = padding / 8;
    }
    else
    {
        if (padding = 64 - (input.size() + 9) % 64; padding >= 64) padding = 0;
        padding = padding / 4;
    }

    for (int x=0; x < padding; x++)
    {
        calculateWorkingVariables(static_cast<T>(0), workingVariables, constantIndex);
        messageSchedule.emplace_back(static_cast<T>(0));
    }
}

template <typename T>
void addMessageSize(uint64_t byteSize, vector<T>& workingVariables, vector<T>& messageSchedule, size_t& constantIndex)
{
    if (sizeof(T) < sizeof(uint64_t))
    {
        calculateWorkingVariables(static_cast<T>((byteSize & 0xffffffff00000000) >> 32), workingVariables,
            constantIndex);
        messageSchedule.emplace_back((byteSize & 0xffffffff00000000) >> 32);
        calculateWorkingVariables(static_cast<T>(byteSize & 0x00000000ffffffff), workingVariables, constantIndex);
        messageSchedule.emplace_back(byteSize & 0x00000000ffffffff);
    }
    else
    {
        calculateWorkingVariables(static_cast<T>(0), workingVariables, constantIndex);
        messageSchedule.emplace_back(0);
        calculateWorkingVariables(static_cast<T>(byteSize), workingVariables, constantIndex);
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
            processMessageSchedule(messageSchedule, workingVariables, output, constantIndex, numberOfLoops);
    }

    addPadding(input, messageSchedule, workingVariables, constantIndex);
    addMessageSize(byteSize, workingVariables, messageSchedule, constantIndex);
    processMessageSchedule(messageSchedule, workingVariables, output, constantIndex, numberOfLoops);

    return output;
}

void performOnBlock(const array<uint32_t, 16>& block, array<uint32_t, 4>& currentHash, const unsigned char roundNumber,
    const function<uint32_t(uint32_t, uint32_t, uint32_t)>& operation)
{
    for (int x=0; x < block.size(); x++)
    {
        const uint32_t value = rotl(operation(currentHash[1], currentHash[2], currentHash[3]) + currentHash[0] +
            block[MD5_FEED_ORDER[x + roundNumber * 16]] + MD5_CONSTANTS[x + roundNumber * 16],
            MD5_ROTATE[x + roundNumber * 16]) + currentHash[1];

        currentHash[0] = currentHash[3];
        currentHash[3] = currentHash[2];
        currentHash[2] = currentHash[1];
        currentHash[1] = value;
    }
}

uint32_t F(const uint32_t a, const uint32_t b, const uint32_t c)
{
    return (a & b) | ((~a) & c);
}

uint32_t G(const uint32_t a, const uint32_t b, const uint32_t c)
{
    return (a & c) | (b & (~c));
}


uint32_t H(const uint32_t a, const uint32_t b, const uint32_t c)
{
    return a ^ b ^ c;
}

uint32_t I(const uint32_t a, const uint32_t b, const uint32_t c)
{
    return b ^ (a & (~c));
}

void performBlockCalculations(array<uint32_t, 16>& messageSection, array<uint32_t, 4>& currentHash)
{
    performOnBlock(messageSection, currentHash, 0, F);
    performOnBlock(messageSection, currentHash, 1, G);
    performOnBlock(messageSection, currentHash, 2, H);
    performOnBlock(messageSection, currentHash, 3, I);

    messageSection = {0};
}

vector<uint32_t> calculateMd5(const string& input)
{
    array<uint32_t, 4> hash  = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};
    array<uint32_t, 16> messageSection = {0};
    size_t currentIndex = 0, currentWord = 0;
    uint64_t byteSize = input.size() * 8;

    while (currentIndex < input.size())
    {
        while (currentWord < 16 && currentIndex < input.size())
        {
            messageSection[currentWord] = getNextWord<uint32_t>(input, currentIndex);
            currentWord++;
        }

        if (currentWord == 16) performBlockCalculations(messageSection, hash);
    }

    if (currentWord < 14)
    {
        messageSection[14] = (byteSize & 0xffffffff00000000) >> 32;
        messageSection[15] = (byteSize & 0x00000000ffffffff);
        performBlockCalculations(messageSection, hash);
    }
    else
    {
        performBlockCalculations(messageSection, hash);
        messageSection[14] = (byteSize & 0xffffffff00000000) >> 32;
        messageSection[15] = (byteSize & 0x00000000ffffffff);
        performBlockCalculations(messageSection, hash);
    }

    return vector<uint32_t>{hash.begin(), hash.end()};
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

string Hash::md5(const string& data)
{
    const auto md5NumericValue = calculateMd5(data);
    return DataConverter::convertDataToHexString(md5NumericValue);
}