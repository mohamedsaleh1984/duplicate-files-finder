/*
    Copyright © 2025 Mohamed Saleh. All Rights Reserved.

    This software and its source code are the exclusive property of Mohamed Saleh.
    Unauthorized copying, modification, distribution, or use of this software,
    in whole or in part, is strictly prohibited.

    For licensing inquiries, please contact mohamedsaleh1984@hotmail.com.

*/
#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <iomanip>
using namespace std;

class Utilities
{
public:
    /// @brief Shorten File Name
    /// @param fileNameWOExt give file name without extension
    /// @return new file name
    static std::string shorten_file_name(std::string fileNameWOExt)
    {
        if (fileNameWOExt.length() > 25)
        {
            return fileNameWOExt.substr(0, 22).append("...");
        }
        return fileNameWOExt;
    }
};

#endif