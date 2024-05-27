/*******************************************************
* Created by Cryos on 5/26/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#include <gtest/gtest.h>
#include "DataConverter.h++"

using namespace std;
using namespace StiltFox::StandMixer;

TEST(DataConverter, convertDataToHexString_will_convert_unsigned_char_array_to_hexadecimal)
{
    //given we have some hexadecimal values
    unsigned char data[48] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                              0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
                              0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f};

    //when we convert the data to a hex string
    auto actual = DataConverter::convertDataToHexString(data, 48);

    //then we get back the expected hex string
    EXPECT_EQ(actual, "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f");
}

TEST(DataConverter, convertDataToHexString_will_convert_unsigned_char_vector_to_hexidecimal)
{
    //given we have some data in a vector
    vector<unsigned char> data = {0xff, 0x5a, 0xaa, 0xac, 0x34, 0x01};

    //when we convert the data to a hex string
    auto actual = DataConverter::convertDataToHexString(data);

    //then we get back the expected hex string
    EXPECT_EQ(actual, "ff5aaaac3401");
}

TEST(DataConverter, convertDataToBinaryString_will_convert_unsigned_char_data_to_binary_string)
{
    //given we have some data
    unsigned char data[] = {0x09, 0x7a, 0xff};

    //when we convert the data to a binary string
    auto actual = DataConverter::convertDataToBinaryString(data, 3);

    //then we get back the expected binary string
    EXPECT_EQ(actual, "000010010111101011111111");
}

TEST(DataConverter, convertDataToBinaryString_will_convert_unsigned_char_vector_to_binary_string)
{
    //given we have some data
    vector<unsigned char> data = {0x09, 0x7a, 0xff};

    //when we convert the data to a binary string
    auto actual = DataConverter::convertDataToBinaryString(data);

    //then we get back the expected binary string
    EXPECT_EQ(actual, "000010010111101011111111");
}