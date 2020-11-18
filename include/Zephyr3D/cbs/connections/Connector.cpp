#include "Connector.h"

#include "../Object.h"

zephyr::cbs::Connector::Connector(Component* owner)
    : m_Owner(owner) {
    m_Owner->Object().RegisterConnector(this);
}
