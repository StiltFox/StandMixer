/*******************************************************
* Created by Cryos on 5/26/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#ifndef StiltFox_STANDMIXER_SRC_MAIN_DATA_CONVERTER_DATACONVERTER_H
#define StiltFox_STANDMIXER_SRC_MAIN_DATA_CONVERTER_DATACONVERTER_H
#include <string>
#include <vector>

/***********************************************************************************************************************
 * This namespace contains methods meant for converting data from one format to another. Ex: a char array to a hex
 * string.
 **********************************************************************************************************************/
namespace StiltFox::StandMixer::DataConverter
{
    /*******************************************************************************************************************
     * Converts a standard C based character array into a hexadecimal string.
     * Note: this string will be lowercase.
     *
     * @Param data - This is the data to be translated.
     * @Param length - The number of characters in the array.
     * @Return The hex string representation of the provided data
     ******************************************************************************************************************/
    std::string convertDataToHexString(const unsigned char* data, unsigned long length);
    /*******************************************************************************************************************
     * Converts a C++ vector into a hexadecimal string.
     * Note: this string will be lowercase.
     *
     * @Param data - This is the data to be translated.
     * @Return the hex string representation of the provided data.
     ******************************************************************************************************************/
    std::string convertDataToHexString(std::vector<unsigned char> data);
    /*******************************************************************************************************************
     * Converts a C based character array into a binary string.
     *
     * @Param data - This is the data to be translated.
     * @Param length - The number of characters in the array.
     * @Return The binary string representation of the provided data.
     ******************************************************************************************************************/
    std::string convertDataToBinaryString(const unsigned char* data, unsigned long length);
    /*******************************************************************************************************************
     * Converts a C++ vector into a hexadecimal string.
     *
     * @Param data - This is the data to be translated.
     * @Return The binary string representation of the provided data.
     ******************************************************************************************************************/
    std::string convertDataToBinaryString(std::vector<unsigned char> data);

    /*******************************************************************************************************************
     * Converts a hexadecimal string to a vector of unsigned chars. This function will not throw an exception.
     *
     * @Param hex - The string to be converted back into character data. Case-insensitive.
     * @Return This returns a vector of unsigned characters containing the data represented by the provided string. On
     *         failure, this function returns an empty vector.
     ******************************************************************************************************************/
    std::vector<unsigned char> convertHexStringToData(const std::string& hex);
}
#endif