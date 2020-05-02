#ifndef Sound_h
#define Sound_h

#pragma warning(push, 0)
#include <al.h>
#include <alc.h>

#include <iostream>
#include <string>
#pragma warning(pop)

namespace zephyr::resources {

class Sound {
public:
    explicit Sound(const std::string& path);

    Sound() = delete;
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;
    Sound(Sound&&) = delete;
    Sound& operator=(Sound&&) = delete;
    ~Sound();

    ALuint ID() const { return m_ID; }
    ALint Size() const { return m_Size; }
    ALint Bits() const { return m_Bits; }
    ALint Channels() const { return m_Channels; }
    ALint Frequency() const { return m_Frequency; }
    ALfloat Length() const { return m_Length; }

private:
    ALuint m_ID;

    ALint m_Size;
    ALint m_Bits;
    ALint m_Channels;
    ALint m_Frequency;
    ALfloat m_Length; // In seconds
};

}

#endif
