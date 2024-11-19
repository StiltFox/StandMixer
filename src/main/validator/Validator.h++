/*******************************************************
* Created by Cryos on 5/27/24.
* Copyright 2024 Stilt Fox® LLC
*
* See LICENSE on root project directory for terms
* of use.
********************************************************/
#ifndef StiltFox_STANDMIXER_SRC_MAIN_VALIDATOR_VALIDATOR_H
#define StiltFox_STANDMIXER_SRC_MAIN_VALIDATOR_VALIDATOR_H
#include <string>

/***********************************************************************************************************************
 * This namespace is solely used to validate different bits of data before farther processing.
 **********************************************************************************************************************/
namespace StiltFox::StandMixer::Validator
{
    /*******************************************************************************************************************
     * This function will determine weather or not the passed in string is a valid hexadecimal value.
     *
     * @Param hex - The string to be validated.
     * @Param length - The expected length of the string. The function will fail if this length is not matched by the
     *                 hex string exactly.
     * @Return true if the string is valid hex, false for anything else.
     ******************************************************************************************************************/
    bool hexString(const std::string& hex, int length);
    /*******************************************************************************************************************
     * This function will determine weather or not the passed in string is a valid hexadecimal value.
     *
     * @Param hex - The string to be validated.
     * @Return true if the string is valid hex, false for anything else.
     ******************************************************************************************************************/
    bool hexString(const std::string& hex);
}
#endif
