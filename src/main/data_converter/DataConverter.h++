/*******************************************************
* Created by Cryos on 5/26/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#ifndef StiltFox_STANDMIXER_SRC_MAIN_DATA_CONVERTER_DATACONVERTER_H
#define StiltFox_STANDMIXER_SRC_MAIN_DATA_CONVERTER_DATACONVERTER_H
#include <string>
#include <vector>

namespace StiltFox::StandMixer::DataConverter
{
    std::string convertDataToHexString(unsigned char* data, unsigned long length);
    std::string convertDataToHexString(std::vector<unsigned char> data);
    std::string convertDataToBinaryString(unsigned char* data, unsigned long length);
    std::string convertDataToBinaryString(std::vector<unsigned char> data);
}
#endif
