/*******************************************************
* Created by Cryos on 5/26/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#include <gtest/gtest.h>
#include <Stilt_Fox/Scribe/File.h++>
#include "Hash.h++"

using namespace std;
using namespace StiltFox::StandMixer;
using namespace StiltFox::Scribe;

const string LOREM_IPSUM = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt "
                           "ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation "
                           "ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in "
                           "reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur "
                           "sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est"
                           " laborum.";

TEST(Hash, sha256_returns_the_hash_of_the_data_passed_in)
{
    //given we have a string to take the sha value of
    string toHash = "SCP-049 would like to be let in on the festivities";

    //when we take the hash of the string
    string hash = Hash::sha256(toHash);

    //then we get back the hash of the data
    EXPECT_EQ(hash, "c386fab497743e56f8b2a6df12d3839050ea31859f1479d7938435480c547d4c");
}

TEST(Hash, sha256_returns_the_hash_of_a_larger_string_that_requires_multiple_blocks)
{
    //given we have a long string to take a hash value of
    string toHash = LOREM_IPSUM;

    //when we take the hash of the string
    string hash = Hash::sha256(toHash);

    //then we get back the hash of the data
    EXPECT_EQ(hash, "2d8c2f6d978ca21712b5f6de36c9d31fa8e96a4fa5d8ff8b0188dfb9e7c171bb");
}

TEST(Hash, md5_returns_the_hash_of_the_data_passed_in)
{
    //given we have a string to take the sha value of
    string toHash = "SCP-049 would like to be let in on the festivities";

    //when we take the hash of the string
    string hash = Hash::md5(toHash);

    //then we get back the hash of the data
    EXPECT_EQ(hash, "c93afd2d417699aa996c56e1842544ad");
}

TEST(Hash, sha512_returns_the_hash_of_the_data_passed_in)
{
    //given we have a string to take the sha value of
    string toHash = "SCP-049 would like to be let in on the festivities";

    //when we take the hash of the string
    string hash = Hash::sha512(toHash);

    //then we get back the hash of the data
    EXPECT_EQ(hash, "d61059eda55891549659f14f51e29dcee49d484342eb0181ad7ec2d95188501e6f9931dba40743287ec610e9f8c2119ef1"
                    "50d9038febc23698e2f11429823d9a");
}

TEST(Hash, sha512_returns_the_hash_of_a_larger_string_that_requires_multiple_blocks)
{
    //given we have a string to take the sha value of
    string toHash = LOREM_IPSUM;

    //when we take the hash of the string
    string hash = Hash::sha512(toHash);

    //then we get back the hash of the data
    EXPECT_EQ(hash, "8ba760cac29cb2b2ce66858ead169174057aa1298ccd581514e6db6dee3285280ee6e3a54c9319071dc8165ff061d77783"
                    "100d449c937ff1fb4cd1bb516a69b9");
}