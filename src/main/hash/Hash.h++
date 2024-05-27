/*******************************************************
* Created by Cryos on 5/24/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#ifndef StiltFox_STANDMIXER_SRC_MAIN_HASH_HASH_H
#define StiltFox_STANDMIXER_SRC_MAIN_HASH_HASH_H
#include <string>

namespace StiltFox::StandMixer::Hash
{
    std::string sha256(std::string data);
    std::string sha512(std::string data);
    std::string md5(std::string data);
}
#endif