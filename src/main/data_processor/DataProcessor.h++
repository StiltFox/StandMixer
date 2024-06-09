/*******************************************************
* Created by Cryos on 5/31/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#ifndef StiltFox_STANDMIXER_SRC_MAIN_DATA_PROCESSOR_DATAPROCESSOR_H
#define StiltFox_STANDMIXER_SRC_MAIN_DATA_PROCESSOR_DATAPROCESSOR_H
#include <unordered_set>
#include <vector>
#include <string>

namespace StiltFox::StandMixer::DataProcessor
{
    std::vector<std::string> tokenize(const std::string& data, const std::string& delim = " ");

    template<typename T>
    std::unordered_set<T> getUnion(const std::unordered_set<T>& set1, const std::unordered_set<T>& set2)
    {
        std::unordered_set<T> output;

        for (auto item : set1) output.emplace(item);
        for (auto item : set2) output.emplace(item);

        return output;
    }
}
#endif
