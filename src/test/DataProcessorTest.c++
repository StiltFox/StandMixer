/*******************************************************
* Created by Cryos on 5/31/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#include <gtest/gtest.h>
#include "DataProcessor.h++"

using namespace std;
using namespace StiltFox::StandMixer;

TEST(DataProcessor, tokenize_will_return_a_vector_with_one_entry_containing_the_whole_data_if_deliminator_is_not_found)
{
    //given we have a string with no deliminator in it
    const string data = "this string has no deliminators in it";

    //when we tokenize the string
    const auto actual = DataProcessor::tokenize(data, ";");

    //then we get back a single element vector with the initial string
    vector<string> expected = {"this string has no deliminators in it"};
    EXPECT_EQ(actual, expected);
}

TEST(DataProcessor, tokenize_will_default_to_space_if_no_delimitor_is_provided)
{
    //given we have a string that has spaces
    string data = "We're going to be playing vaporwave in the office today";

    //when we tokenize the string
    auto actual = DataProcessor::tokenize(data);

    //then we get back the tokenized vector
    vector<string> expected = {"We're", "going", "to", "be", "playing", "vaporwave", "in", "the", "office", "today"};
    EXPECT_EQ(actual, expected);
}

TEST(DataProcessor, tokenize_can_handle_multi_character_delimitors)
{
    //given we have a string with some delimiters
    string data = "This&nbsp;is&nbsp;using&nbsp;HTML&nbsp;spaces";

    //when we tokenize the string
    auto actual = DataProcessor::tokenize(data, "&nbsp;");

    //then we get back the tokenized vector
    vector<string> expected = {"This", "is", "using", "HTML", "spaces"};
    EXPECT_EQ(actual, expected);
}

TEST(DataProcessor, tokenize_will_empty_a_queue_if_that_is_used_for_input)
{
    //given we have a queue of characters with some delimiters
    string data = "This&nbsp;is&nbsp;using&nbsp;HTML&nbsp;spaces";
    queue dataQueue(deque(data.begin(), data.end()));

    //when we tokenize the queue
    auto actual = DataProcessor::tokenize(dataQueue, "&nbsp;");

    //then we get back the tokenized vector and the queue is empty
    vector<string> expected = {"This", "is", "using", "HTML", "spaces"};
    EXPECT_EQ(actual, expected);
    EXPECT_TRUE(dataQueue.empty());
}

TEST(DataProcessor, getUnion_will_return_the_union_of_two_sets)
{
    //given we have two sets with some overlap
    unordered_set<string> set1 = {"a","b","c","d"};
    unordered_set<string> set2 = {"a","2","b","1","5"};

    //when we create a union of the sets
    auto actual = DataProcessor::getUnion(set1, set2);

    //then we get back the union of the sets
    unordered_set<string> expected = {"a","2","b","1","5","c","d"};
    EXPECT_EQ(actual,expected);
}