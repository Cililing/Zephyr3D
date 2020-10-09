#include "Connector.h"

#include "../Object.h"

Connector::Connector(Component* owner)
    : m_Owner(owner) {
    //m_Owner->Object().ConnectionsManager().RegisterConnector(this);
}
