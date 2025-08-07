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
#include <queue>

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
     * This function will split the characters in the queue into a vector of tokens (small pieces of a string that are
     * sectioned off by a deliminator). The queue will be emptied in the process.
     *
     * @param data - the queue containing the data to be split up. The queue data will not be saved. The queue will be
     *               empty after processing. Be careful of this when calling this function.
     * @Param delim - This is the deliminator that will be used to split the string up. By default, this is a single
     *                Space.
     * @Return A vector of strings that contains the tokens, in order read. For example "who are you" with a delim of
     *         " " would produce {"who", "are", "you"}.
     ******************************************************************************************************************/
    std::vector<std::string> tokenize(std::queue<char>& data, const std::string& delim = " ");
    /*******************************************************************************************************************
     * This function will retrieve a subset of the given string, up to the first instance of the provided deliminator.
     *
     * @param data - the string to search for the deliminator in.
     * @param delim - the deliminator to search for.
     * @return A part of the string that was passed in, up to but not including the first instance found of the
     *         deliminator. For example if we had the string "Bob is my sworn Enemy" and we used a delim of " " then we
     *         would get back "Bob".
     ******************************************************************************************************************/
    std::string parseToDelimiter(const std::string& data, const std::string& delim = " ");
    /*******************************************************************************************************************
     * This function will retrieve a subset of the characters contained within the queue. The queue will be partially
     * emptied up to the provided deliminator.
     *
     * @param data - the queue containing the characters you wish to parse. Keep in mind that this queue will be
     *               partially emptied, or in some cases fully emptied. Check for emptiness of queue before doing
     *               farther processing with your own code.
     * @param delim - the deliminator to stop at.
     * @return A section of the data contained in the queue up to but not including the first instance found of the
     *         deliminator. The queue will be emptied of used characters. For example if we had the following queue
     *         {'b','o','y',' ','g','i','r','l'} then called this with a delim of " "; we would get back "Boy" and
     *         the queue would have {'g','i','r','l'} remaining.
     ******************************************************************************************************************/
    std::string parseToDelimiter(std::queue<char>& data, const std::string& delim = " ");
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
