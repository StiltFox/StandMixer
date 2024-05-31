/*******************************************************
* Created by Cryos on 5/27/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#ifndef StiltFox_STANDMIXER_SRC_MAIN_VALIDATOR_VALIDATOR_H
#define StiltFox_STANDMIXER_SRC_MAIN_VALIDATOR_VALIDATOR_H
#include <string>

namespace StiltFox::StandMixer::Validator
{
    bool hexString(const std::string& hex, int length);
    bool hexString(const std::string& hex);
}
#endif
