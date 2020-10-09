#ifndef MessageOut_h
#define MessageOut_h

#include "AbstractConnectors.h"

template <class M>
class MessageOut final : public AbstractMessageOut {
public:
    MessageOut(Component* owner)
        : AbstractMessageOut(owner) {

    }

    MessageOut() = delete;
    MessageOut(const MessageOut&) = delete;
    MessageOut& operator=(const MessageOut&) = delete;
    MessageOut(MessageOut&&) = delete;
    MessageOut& operator=(MessageOut&&) = delete;
    ~MessageOut() = default;

    void Send(M& message);
};

#include "ConnectionsManager.h"

template <class M>
void MessageOut<M>::Send(M& message) {
    m_ConnectionsManager->ForwardMessage(*this, &message);
}

#endif
