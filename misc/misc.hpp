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


template<typename Func, typename ... Args>
auto measureExecutionTime(Func &&func, Args &&... args) {
	auto start = std::chrono::high_resolution_clock::now();

	// void function
	if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>) {
		// Handle void return type
		std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
		auto end = std::chrono::high_resolution_clock::now();
		auto milliseconds =
				std::chrono::duration_cast<std::chrono::nanoseconds>(
						end - start);
		return milliseconds; // Only return the duration for void functions
	} else {
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
#endif
