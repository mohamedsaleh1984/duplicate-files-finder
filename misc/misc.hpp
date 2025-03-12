/*
    Copyright © 2025 Mohamed Saleh. All Rights Reserved.

    This software and its source code are the exclusive property of Mohamed Saleh.
    Unauthorized copying, modification, distribution, or use of this software,
    in whole or in part, is strictly prohibited.

    For licensing inquiries, please contact mohamedsaleh1984@hotmail.com.

*/

#ifndef _MISC_H__
#define _MISC_H__

#include <thread>
#include <chrono>

const unsigned int DURATION = 200;

/// @brief loading with cross platform sleep
void loading()
{
    while (1)
    {
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoading   " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
        std::cout << "\b\b\b\b\b\b\b\b\b\bLOading   " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoAding   " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoaDing   " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoadIng   " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoadiNg   " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoadinG   " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoading.  " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoading.." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoading..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
    }
}

template <typename Func, typename... Args>
auto genericMeasureExecutionTime(Func &&func, Args &&...args)
{
    auto start = std::chrono::high_resolution_clock::now();

    // void function
    if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>)
    {
        // Handle void return type
        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        auto milliseconds =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                end - start);
        return milliseconds; // Only return the duration for void functions
    }
    else
    {
        // Handle non-void return type
        auto result = std::invoke(std::forward<Func>(func),
                                  std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        auto milliseconds =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                end - start);
        return std::make_pair(result, milliseconds); // Return result and duration
    }
}

template <typename Func, typename... Args>
auto measureExecutionTime(Func &&func, Args &&...args)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto result = std::forward<Func>(func)(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " ms\n";

    return result; // Return function result if needed
}

void printUsage(const std::string &programName)
{
    std::cerr << "Usage: " << programName << " [options] arguments\n";
    std::cerr << "Options:\n";
    std::cerr << "  -d, --delete       Delete duplicates without asking\n";
    std::cerr << "  -v, --view        Show duplicate files paths\n";
    std::cerr << "Arguments:\n";
    std::cerr << "  input_directory      Path to the root directory\n";
}
#endif
