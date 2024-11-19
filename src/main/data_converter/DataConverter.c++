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

string DataConverter::convertDataToHexString(const unsigned char* data, const unsigned long length)
{
    stringstream output;

    for(int i=0; i<length; i++) output << hex << setw(2) << setfill('0') << static_cast<int>(data[i]);

    return output.str();
}

string DataConverter::convertDataToHexString(vector<unsigned char> data)
{
    return convertDataToHexString(data.data(), data.size());
}

string DataConverter::convertDataToBinaryString(const unsigned char* data, const unsigned long length)
{
    stringstream output;

    for(int i=0; i<length; i++) output << bitset<8>(data[i]);

    return output.str();
}

string DataConverter::convertDataToBinaryString(std::vector<unsigned char> data)
{
    return convertDataToBinaryString(data.data(), data.size());
}

std::vector<unsigned char> DataConverter::convertHexStringToData(const std::string& hex)
{
    std::vector<unsigned char> output;

    if (hex.length() % 2 == 0)
    {
        try
        {
            for (int i=0; i<hex.length(); i+=2)
            {
                output.push_back(stoi(hex.substr(i, 2), nullptr, 16));
            }
        }
        catch (...)
        {
            output.clear();
        }
    }

    return output;
}
