/*******************************************************
* Created by Cryos on 5/24/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#ifndef StiltFox_STANDMIXER_SRC_MAIN_HASH_HASH_H
#define StiltFox_STANDMIXER_SRC_MAIN_HASH_HASH_H
#include <string>

/***********************************************************************************************************************
 * This namespace exists to enable hashing functions. The base libraries that handle hashing can be incredibly difficult
 * to use. These wrapper functions simplify the process a lot.
 **********************************************************************************************************************/
namespace StiltFox::StandMixer::Hash
{
    /*******************************************************************************************************************
     * This function will take any data and convert it into a sha256 hash. If you want to add a salt you must add
     * it yourself before passing it in. Note that a string is just a vector of char basically, so if you have numeric
     * data, you can just cast it to char* and build a new string with it.
     *
     * @Param data - a string containing the binary data that should be hashed.
     * @Return a hexadecimal string that represents the hash
     ******************************************************************************************************************/
    std::string sha256(std::string data);
    /*******************************************************************************************************************
     * This function will take any data and convert it into a sha512 hash. If you want to add a salt you must add
     * it yourself before passing it in. Note that a string is just a vector of char basically, so if you have numeric
     * data, you can just cast it to char* and build a new string with it.
     *
     * @Param data - a string containing the binary data that should be hashed.
     * @Return a hexadecimal string that represents the hash
     ******************************************************************************************************************/
    std::string sha512(std::string data);
    /*******************************************************************************************************************
     * This function will take any data and convert it into a md5 hash. If you want to add a salt you must add it
     * yourself before passing it in. Note that a string is just a vector of char basically, so if you have numeric
     * data, you can just cast it to char* and build a new string with it.
     *
     * @Param data - a string containing the binary data that should be hashed.
     * @Return a hexadecimal string that represents the hash
     ******************************************************************************************************************/
    std::string md5(std::string data);
}
#endif