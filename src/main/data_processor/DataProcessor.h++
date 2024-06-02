/*******************************************************
* Created by Cryos on 5/31/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#ifndef StiltFox_STANDMIXER_SRC_MAIN_DATA_PROCESSOR_DATAPROCESSOR_H
#define StiltFox_STANDMIXER_SRC_MAIN_DATA_PROCESSOR_DATAPROCESSOR_H
#include <vector>
#include <string>

namespace StiltFox::StandMixer::DataProcessor
{
    std::vector<std::string> tokenize(const std::string& data, const std::string& delim = " ");
}
#endif
