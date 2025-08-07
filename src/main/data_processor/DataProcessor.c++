/*******************************************************
* Created by Cryos on 5/31/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#include "DataProcessor.h++"

using namespace std;

namespace StiltFox::StandMixer
{
    vector<string> DataProcessor::tokenize(const string& data, const string& delim)
    {
        queue dataQueue(deque(data.begin(), data.end()));
        return tokenize(dataQueue, delim);
    }

    vector<string> DataProcessor::tokenize(queue<char>& data, const string& delim)
    {
        vector<string> tokenizedVector;

        while (!data.empty()) tokenizedVector.push_back(parseToDelimiter(data, delim));

        return tokenizedVector;
    }

    string DataProcessor::parseToDelimiter(const string& data, const string& delim)
    {
        queue dataQueue(deque(data.begin(), data.end()));
        return parseToDelimiter(dataQueue, delim);
    }

    string DataProcessor::parseToDelimiter(queue<char>& data, const string& delim)
    {
        string output;

        while (!data.empty() && !output.ends_with(delim))
        {
            output += data.front();
            data.pop();
        }
        if (output.ends_with(delim)) output = output.substr(0, output.size() - delim.size());

        return output;
    }
}