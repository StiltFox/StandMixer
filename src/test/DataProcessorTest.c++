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
    string data = "this string has no deliminators in it";

    //when we tokenize the string
    auto actual = DataProcessor::tokenize(data, ";");

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