#ifndef MessageOut_h
#define MessageOut_h

#include "AbstractConnectors.h"

class ConnectionsManager;

template <class M>
class MessageOut final : public AbstractMessageOut {
    friend class ConnectionsManager;

public:
    MessageOut(Component* owner)
        : AbstractMessageOut(owner)
        , m_ConnectionsManager(nullptr) {}

    MessageOut() = delete;
    MessageOut(const MessageOut&) = delete;
    MessageOut& operator=(const MessageOut&) = delete;
    MessageOut(MessageOut&&) = delete;
    MessageOut& operator=(MessageOut&&) = delete;
    ~MessageOut() = default;

    void Send(M& message);

private:
    ConnectionsManager* m_ConnectionsManager;
};

#include "ConnectionsManager.h"

template <class M>
void MessageOut<M>::Send(M& message) {
    if (m_ConnectionsManager) {
        m_ConnectionsManager->ForwardMessage(this, &message);
    }
}

#endif
