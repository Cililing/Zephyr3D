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
    void Initialize() override;
    void Update() override;

    MessageOut<std::string> DebugInfo{ this };
};

#endif
