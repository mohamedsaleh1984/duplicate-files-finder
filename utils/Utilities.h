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

    /// @brief Present bytes in readable format.
    /// @param bytes
    /// @return
    static std::string bytesToSize(unsigned long long bytes)
    {
        const std::string sizes[] = {"Bytes", "KB", "MB", "GB", "TB"};
        if (bytes == 0)
            return "n/a";

        int i = static_cast<int>(std::floor(std::log(bytes) / std::log(1024)));
        if (i == 0)
            return std::to_string(bytes) + " " + sizes[i];

        char result[20];
        std::sprintf(result, "%.1f %s", bytes / std::pow(1024, i), sizes[i].c_str());

        return std::string(result);
    }

    /// @brief Convert milliseconds to hours.
    /// @param milliseconds
    /// @return
    static int milliseconds_to_hours(unsigned long long milliseconds)
    {
        int seconds = milliseconds / 1000;
        int hours = seconds / 3600;
        return hours;
    }

    /// @brief Convert milliseconds to hours.
    /// @param milliseconds
    /// @return
    static int milliseconds_to_minutes(unsigned long long milliseconds)
    {
        int seconds = milliseconds / 1000;
        int minutes = seconds / 60;
        return minutes;
    }
};

#endif