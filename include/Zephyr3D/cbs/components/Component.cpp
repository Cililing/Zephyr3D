#include "Component.h"

#include "../Object.h"
#include "../connections/AbstractConnectors.h"

void Component::RegisterUpdateCall() const {
    m_Object->RegisterUpdateCall(this);
}

void Component::UnregisterUpdateCall() const {
    m_Object->UnregisterUpdateCall(this);
}
