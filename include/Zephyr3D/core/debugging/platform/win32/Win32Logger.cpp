#include "Win32Logger.h"

zephyr::Logger& zephyr::Logger::Instance() {
    static Logger instance;

    return instance;
}

zephyr::Logger::Logger() {
    m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    m_ChannelMask = EChannel::Info | EChannel::Warning | EChannel::Error;
}

void zephyr::Logger::Push(EChannel channel) {
    m_ChannelMask = m_ChannelMask | channel;
}

void zephyr::Logger::Pop(EChannel channel) {
    m_ChannelMask = m_ChannelMask | (~channel);
}

void zephyr::Logger::InfoLog(ESender sender, const char* file, int line, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Info)) {
        SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(sender));

        va_list argptr;
        va_start(argptr, format);
        printf("%s %d: ", file, line);
        vfprintf(stdout, format, argptr);
        printf("\n");
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(ESender::None));
    }
}

void zephyr::Logger::WarningLog(ESender sender, const char* file, int line, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Warning)) {
        SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(sender));

        va_list argptr;
        va_start(argptr, format);
        printf("WARNING %s %d: ", file, line);
        vfprintf(stdout, format, argptr);
        printf("\n");
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(ESender::None));
    }
}

void zephyr::Logger::ErrorLog(ESender sender, const char* file, int line, const char* format, ...) {
    if (static_cast<unsigned char>(m_ChannelMask & EChannel::Error)) {
        SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(sender));

        va_list argptr;
        va_start(argptr, format);
        printf("ERROR %s %d: ", file, line);
        vfprintf(stdout, format, argptr);
        printf("\n");
        va_end(argptr);

        // Return to default state white text on black background
        SetConsoleTextAttribute(m_ConsoleHandle, static_cast<WORD>(ESender::None));
    }
}
