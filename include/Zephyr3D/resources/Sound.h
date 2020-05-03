#ifndef Sound_h
#define Sound_h

#pragma warning(push, 0)
#include <al.h>
#include <alc.h>

#include <iostream>
#include <string>
#pragma warning(pop)

namespace zephyr::resources {

class AudioClip {
public:
    explicit AudioClip(const std::string& path);

    AudioClip() = delete;
    AudioClip(const AudioClip&) = delete;
    AudioClip& operator=(const AudioClip&) = delete;
    AudioClip(AudioClip&&) = delete;
    AudioClip& operator=(AudioClip&&) = delete;
    ~AudioClip();

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
