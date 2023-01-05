#pragma once


#define NODISCARD           [[nodiscard]]   
#define NOEXCEPT            noexcept        

#define SOLAR_BEGIN namespace solar {
#define SOLAR_END   }

#include <cstdint>
typedef std::uint32_t       Handle;

#if defined(SOLAR_USE_CASSERT)
#pragma once
#include <cassert>
#define SOLAR_ASSERT(condition, message) assert((condition) && (message))
#else
#define SOLAR_ASSERT
#endif

#if defined(_WIN32)
    #if defined(_WIN64)
        #define SOLAR_WINDOWS
        #include <Windows.h>
#define SOLAR_MAIN (CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow))
    #endif
#else
    #error "Couldn't compile on x86!"
#endif

#if defined(__linux__)
#define SOLAR_LINUX
#include <unistd.h>
#define SOLAR_MAIN (main(const int argc, const char** argv, const char** envp))
#elif defined(__APPLE__)
#error "Couldn't compile on MacOS!
#endif

#define SOLAR_VERSION_MAJOR 1
#define SOLAR_VERSION_MINOR 0
#define SOLAR_VERSION_PATCH 0
#define SOLAR_VERSION SOLAR_VERSION_MAJOR << 16 & 0xFF0000 | SOLAR_VERSION_MINOR << 8 & 0xFF00 | SOLAR_VERSION_PATCH;