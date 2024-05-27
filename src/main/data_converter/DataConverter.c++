/*******************************************************
* Created by Cryos on 5/26/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#include "DataConverter.h++"
#include <sstream>
#include <iomanip>
#include <bitset>

using namespace std;
using namespace StiltFox::StandMixer;

string DataConverter::convertDataToHexString(unsigned char* data, unsigned long length)
{
    stringstream output;

    for(int i=0; i<length; i++) output << hex << setw(2) << setfill('0') << (int)data[i];

    return output.str();
}

string DataConverter::convertDataToHexString(vector<unsigned char> data)
{
    return convertDataToHexString(data.data(), data.size());
}

string DataConverter::convertDataToBinaryString(unsigned char* data, unsigned long length)
{
    stringstream output;

    for(int i=0; i<length; i++) output << bitset<8>(data[i]);

    return output.str();
}

string DataConverter::convertDataToBinaryString(std::vector<unsigned char> data)
{
    return convertDataToBinaryString(data.data(), data.size());
}