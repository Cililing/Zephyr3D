#ifndef TriggerOut_h
#define TriggerOut_h

#include "AbstractConnectors.h"

class ConnectionsManager;

class TriggerOut final : public AbstractTriggerOut {
    friend class ConnectionsManager;

public:
    TriggerOut(Component* owner)
        : AbstractTriggerOut(owner)
        , m_ConnectionsManager(nullptr) {}

    TriggerOut(const TriggerOut&) = delete;
    TriggerOut& operator=(const TriggerOut& other) = delete;
    TriggerOut(TriggerOut&&) = delete;
    TriggerOut& operator=(TriggerOut&&) = delete;
    ~TriggerOut() = default;

    void Trigger() override;

private:
    ConnectionsManager* m_ConnectionsManager;
};

#endif
