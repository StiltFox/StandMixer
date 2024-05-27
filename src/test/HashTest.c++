/*******************************************************
* Created by Cryos on 5/26/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#include <gtest/gtest.h>
#include "Hash.h++"

using namespace std;
using namespace StiltFox::StandMixer;

TEST(Hash, sha256_returns_the_hash_of_the_data_passed_in)
{
    //given we have a string to take the sha value of
    string toHash = "SCP-049 would like to be let in on the festivities";

    //when we take the hash of the string
    string hash = Hash::sha256(toHash);

    //then we get back the hash of the data
    EXPECT_EQ(hash, "c386fab497743e56f8b2a6df12d3839050ea31859f1479d7938435480c547d4c");
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
    EXPECT_EQ(hash, "d61059eda55891549659f14f51e29dcee49d484342eb0181ad7ec2d95188501e6f9931dba40743287ec610e9f8c2119ef150d9038febc23698e2f11429823d9a");
}