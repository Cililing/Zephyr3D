#ifndef Connector_h
#define Connector_h

#include "../components/Component.h"


class Connector {
    friend class ConnectionsManager;

public:
    using ID_t = int;

    Connector(Component* owner);

    Connector() = delete;
    Connector(const Connector&) = delete;
    Connector& operator=(const Connector&) = delete;
    Connector(Connector&&) = delete;
    Connector& operator=(Connector&&) = delete;
    virtual ~Connector() = default;

    ID_t ID() const { return m_ID; }
    Component* Owner() { return m_Owner; }

protected:
    Component* m_Owner;

private:
    ID_t m_ID = -1;
};

#endif
