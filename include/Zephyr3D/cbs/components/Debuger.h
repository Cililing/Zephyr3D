#ifndef DEBUGER_H
#define DEBUGER_H

#include "Component.h"
#include "../Object.h"
#include "../../scenes/Scene.h"
#include "../connections/MessageOut.h"
#include "../../Engine.h"

#include <string>

class Debuger : public Component {
public:
    Debuger(class Object& object, ID_t id);

    void Initialize() override;
    void Update() override;

    MessageOut<std::string> DebugInfo{ this };
};

#endif
