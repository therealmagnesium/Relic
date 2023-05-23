#pragma once
#include <string>

namespace Relic { namespace IO
{
    /* Returns true if the file is found 
     * arguments:
     *  - fileName: the name of the file relative tot he data folder */
    bool DoesFileExist(const std::string& fileName);

    /* Writes a number to a binary file
     * arguments:
     *  - num: the number to be written to the file
     *  - fileName: the name of the file releative to the data folder */
    void WriteNumberToFile(int num, const std::string& fileName);
    

    /* Reads a number from a binary file
     * arguments:
     *  - fileName: the name of the file relative to the data folder */
    int ReadNumberFromFile(const std::string& fileName);
}}
