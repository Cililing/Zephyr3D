#include "Component.h"

#include "../Object.h"
#include "../connections/AbstractConnectors.h"

zephyr::cbs::Component::Component(class Object& object, ID_t id)
    : m_Object(object)
    , m_ID(id) { }

void zephyr::cbs::Component::RegisterUpdateCall() const {
    m_Object.RegisterUpdateCall(this);
}

void zephyr::cbs::Component::UnregisterUpdateCall() const {
    m_Object.UnregisterUpdateCall(this);
}
