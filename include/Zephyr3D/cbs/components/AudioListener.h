#ifndef AudioListener_h
#define AudioListener_h

#include "Component.h"
#include "../connections/PropertyIn.h"

class Transform;
class AudioListener : public Component {
public:
    void Initialize() override;
    void Update() override;

    PropertyIn<Transform*> TransformIn{ this };

};

#endif
