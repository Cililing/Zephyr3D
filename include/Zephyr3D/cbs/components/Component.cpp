#include "Component.h"

#include "../Object.h"
#include "../connections/AbstractConnectors.h"

zephyr::cbs::Component::Component(class Object& object, ID_t id)
    : object(object)
    , m_ID(id) { }

void zephyr::cbs::Component::RegisterUpdateCall() const {
    object.RegisterUpdateCall(this);
}

void zephyr::cbs::Component::UnregisterUpdateCall() const {
    object.UnregisterUpdateCall(this);
}
