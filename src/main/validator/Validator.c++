/*******************************************************
* Created by Cryos on 5/27/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#include "Validator.h++"

using namespace std;
using namespace StiltFox::StandMixer;

bool Validator::hexString(const string& hex)
{
    return Validator::hexString(hex, -1);
}

bool Validator::hexString(const string& hex, int length)
{
    return (length <= 0 || hex.size() == length) && hex.find_first_not_of("0123456789abcdefABCDEF") == string::npos;
}