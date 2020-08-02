#include "AudioManager.h"

void AudioManager::Initialize() {
    INFO_LOG(Logger::ESender::Audio, "Initializing audio manager");

    m_Device = alcOpenDevice(nullptr);

    assert(m_Device);

    m_Context = alcCreateContext(m_Device, nullptr);
    alcMakeContextCurrent(m_Context);
}

void AudioManager::Destroy() {
    INFO_LOG(Logger::ESender::Audio, "Exiting audio manager");

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_Context);
    alcCloseDevice(m_Device);
}

void AudioManager::ListenerPosition(float x, float y, float z) {
    alListener3f(AL_POSITION, x, y, z);
}

void AudioManager::ListenerVelocity(float x, float y, float z) {
    alListener3f(AL_VELOCITY, x, y, z);
}

void AudioManager::ListenerGain(float gain) {
    alListenerf(AL_GAIN, gain);
}

void AudioManager::ListenerOrientation(float at_x, float at_y, float at_z, float up_x, float up_y, float up_z) {
    float values[6] = { at_x, at_y, at_z, up_x, up_y, up_z };
    alListenerfv(AL_ORIENTATION, values);
}
