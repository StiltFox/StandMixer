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

string DataConverter::convertDataToHexString(const vector<unsigned char>& data)
{
    return convertDataToHexString(data.data(), data.size());
}

string DataConverter::convertDataToBinaryString(const unsigned char* data, const unsigned long length)
{
    stringstream output;

    for(int i=0; i<length; i++) output << bitset<8>(data[i]);

    return output.str();
}

std::string DataConverter::convertDataToBinaryString(const std::vector<uint32_t>& data)
{
    stringstream output;

    for (const uint32_t word : data) output << bitset<32>(word);

    return output.str();
}

std::string DataConverter::convertDataToHexString(const std::vector<uint32_t>& words)
{
    stringstream output;

    for (const uint32_t word : words) output << hex << setw(8) << setfill('0') << word;

    return output.str();
}

string DataConverter::convertDataToBinaryString(const std::vector<unsigned char>& data)
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