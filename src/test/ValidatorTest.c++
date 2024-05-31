/*******************************************************
* Created by Cryos on 5/27/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#include <gtest/gtest.h>
#include "Validator.h++"

using namespace std;
using namespace StiltFox::StandMixer;

TEST(Validator, hexString_will_return_false_if_the_string_is_longer_than_length)
{
    //given we have a string to validate that's beyond the desired length
    string hexString = "aa90f3";

    //when we validate the hex string
    bool actual = Validator::hexString(hexString, 4);

    //then we get back false
    EXPECT_FALSE(actual);
}

TEST(Validator, hexString_will_return_false_if_the_string_is_less_long_than_length)
{
    //given we have a string to validate that's lower than the desired length
    string hexString = "e88e90";

    //when we validate the hex string
    bool actual = Validator::hexString(hexString, 8);

    //then we get back false
    EXPECT_FALSE(actual);
}

TEST(Validator, hexString_will_return_true_for_a_string_of_any_length_if_length_is_less_than_zero)
{
    //given we have several strings to validate of varying lengths
    vector<string> toValidate = {"a", "f9331e", "00", "06d3aa45118c"};

    //when we validate the hex strings
    vector<bool> actualValues;
    for (const string& hex : toValidate) actualValues.push_back(Validator::hexString(hex, -1));

    //then all strings pass validation
    vector<bool> expected = {true, true, true, true};
    EXPECT_EQ(actualValues, expected);
}

TEST(Validator, hexString_will_return_false_if_string_is_not_valid_hex)
{
    //given we have a string that's not valid hex
    string invalid = "Hi, this is not valid hexadecimal";

    //when we validate the hex string
    bool actual = Validator::hexString(invalid);

    //then we get back false
    EXPECT_FALSE(actual);
}

TEST(Validator, hexString_will_return_true_if_the_string_is_valid_hex_and_the_correct_length)
{
    //given we have a legitimate hex string
    string validHex = "8cbb2a";

    //when we validate the hex string
    bool actual = Validator::hexString(validHex, 6);

    //then we get back true
    EXPECT_TRUE(actual);
}

TEST(Validator, hexString_will_return_true_if_the_hex_string_is_valid_and_length_is_not_provided)
{
    //given we have a legitimate hex string
    string validHex = "eeeeeeeeeeeeeeeeeeee";

    //when we validate the hex string
    bool actual = Validator::hexString(validHex);

    //then we get back true
    EXPECT_TRUE(actual);
}