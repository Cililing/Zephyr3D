#include "AudioSource.h"
#include "Transform.h"

AudioSource::AudioSource() {
    alGenSources(1, &m_ID);
}

AudioSource::~AudioSource() {
    alDeleteSources(1, &m_ID);
}

void AudioSource::Initialize() {
    RegisterUpdateCall();
}

void AudioSource::Update() {
    if (TransformIn.Connected()) {
        glm::vec3 pos = TransformIn.Value()->Position();
        alSource3f(m_ID, AL_POSITION, pos.x, pos.y, pos.z);
    }
}

void AudioSource::Play() {
    assert(SoundIn.Connected());

    alSourcei(m_ID, AL_BUFFER, SoundIn.Value()->ID());
    alSourcePlay(m_ID);
}

void AudioSource::Loop(bool loop) {
    alSourcei(m_ID, AL_LOOPING, loop);
}

