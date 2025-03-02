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

#endif
