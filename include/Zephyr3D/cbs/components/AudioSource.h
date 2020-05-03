#ifndef AudioSource_h
#define AudioSource_h

#include "Component.h"
#include "../connections/PropertyIn.h"

#include "../../resources/AudioClip.h"

#pragma warning(push, 0)
#include <al.h>
#include <alc.h>
#pragma warning(pop)

class Transform;
class AudioSource : public Component {
public:
    AudioSource();
    ~AudioSource();

    void Initialize() override;
    void Update() override;

    void Play();
    void Loop(bool loop);

    PropertyIn<Transform*> TransformIn{ this };
    PropertyIn<zephyr::resources::AudioClip*> SoundIn{ this };

private:
    ALuint m_ID;
};

#endif
