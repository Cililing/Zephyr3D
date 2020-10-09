#include "Component.h"

#include "../Object.h"
#include "../connections/AbstractConnectors.h"

Component::Component(class Object& object, ID_t id)
    : m_Object(object)
    , m_ID(id) { }

void Component::RegisterUpdateCall() const {
    m_Object.RegisterUpdateCall(this);
}

void Component::UnregisterUpdateCall() const {
    m_Object.UnregisterUpdateCall(this);
}
