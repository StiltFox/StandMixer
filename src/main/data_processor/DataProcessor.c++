/*******************************************************
* Created by Cryos on 5/31/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#include "DataProcessor.h++"

using namespace std;
using namespace StiltFox::StandMixer;

vector<string> DataProcessor::tokenize(const string& data, const string& delim)
{
    vector<string> tokenizedVector;
    size_t currentPosition = 0;

    while (currentPosition!=string::npos)
    {
        size_t nextPosition = data.find(delim, currentPosition);
        tokenizedVector.emplace_back(data.substr(currentPosition, nextPosition - currentPosition));
        currentPosition = nextPosition == string::npos ? nextPosition : nextPosition + delim.size();
    }

    return tokenizedVector;
}