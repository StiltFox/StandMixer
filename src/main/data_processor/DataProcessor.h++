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

/***********************************************************************************************************************
 * This namespace houses functions that 'process' data in some way. Usually more complicated than a simple conversion.
 **********************************************************************************************************************/
namespace StiltFox::StandMixer::DataProcessor
{
    /*******************************************************************************************************************
     * This function splits a string into tokens (small pieces of a string that are sectioned off by a deliminator).
     *
     * @Param data - The string to be split up. This string will not be modified.
     * @Param delim - This is the deliminator that will be used to split the string up. By default, this is a single
     *                Space.
     * @Return A vector of strings that contains the tokens, in order read. For example "who are you" with a delim of
     *         " " would produce {"who", "are", "you"}.
     ******************************************************************************************************************/
    std::vector<std::string> tokenize(const std::string& data, const std::string& delim = " ");

    /*******************************************************************************************************************
     * This function will take two unordered_sets and return a third set that has all non-repeating elements in each
     * set passed in.
     *
     * @Param set1 - This is the first set of data.
     * @Param set2 - This is the second set of data.
     * @Return A set that is the union of the two sets passed in. (a set that contains all elements from both sets)
     ******************************************************************************************************************/
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
