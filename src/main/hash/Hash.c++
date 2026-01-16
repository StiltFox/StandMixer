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
#include <cryptopp/sha.h>
#include <cryptopp/md5.h>
#include <iomanip>

using namespace std;
using namespace StiltFox::StandMixer;

template<typename T>
string encrypt(string data, T hasher)
{
    CryptoPP::byte* digest;

    hasher.Update((const CryptoPP::byte*)data.c_str(),data.size());
    digest = new CryptoPP::byte[hasher.DigestSize()];
    hasher.Final(digest);

    string output = DataConverter::convertDataToHexString(digest, hasher.DigestSize());
    delete[] digest;

    return output;
}

string Hash::sha256(string data)
{
    return encrypt(data, CryptoPP::SHA256());
}

string Hash::sha512(string data)
{
    return encrypt(data, CryptoPP::SHA512());
}

string Hash::md5(string data)
{
    return encrypt(data, CryptoPP::Weak1::MD5());
}