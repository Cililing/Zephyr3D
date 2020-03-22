#ifdef _WIN32
#ifndef Win32Logger_h
#define Win32Logger_h

#include "../../../core/Enum.h"

#include <iostream>
#define NOMINMAX
#include <Windows.h>

#define INFO_LOG(sender, ...)                                              \
do {                                                                       \
    Logger::Instance().InfoLog(sender, __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)

#define WARNING_LOG(sender, ...)                                                \
do {                                                                            \
    Logger::Instance().WarningLog(sender, __FILE__, __LINE__, ##__VA_ARGS__);   \
} while(0)

#define ERROR_LOG(sender, ...)                                              \
do {                                                                        \
    Logger::Instance().ErrorLog(sender, __FILE__, __LINE__, ##__VA_ARGS__); \
} while(0)


class Logger {
public:
    enum class EChannel : unsigned char {
        Info = 0x4,
        Warning = 0x2,
        Error = 0x1
    };

    // Windows specific codes for colors
    // Don't add beyond white
    enum class ESender : WORD {
        CBS = 1,        // Blue
        Rendering = 2,  // Green
        Resources = 3,  // Cyan
        Physics = 4,    // Red
        Audio = 5,      //

        None = 15       // White
    };

    static Logger& Instance();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    ~Logger() = default;

    void Push(EChannel channel);
    void Pop(EChannel channel);

    void InfoLog(ESender sender, const char* file, int line, const char* format, ...);
    void WarningLog(ESender sender, const char* file, int line, const char* format, ...);
    void ErrorLog(ESender sender, const char* file, int line, const char* format, ...);

private:
    Logger();

    HANDLE m_ConsoleHandle;
    EChannel m_ChannelMask;
};
ENABLE_BITMASK_OPERATORS(Logger::EChannel);
ENABLE_BITMASK_OPERATORS(Logger::ESender);

#endif
#endif
