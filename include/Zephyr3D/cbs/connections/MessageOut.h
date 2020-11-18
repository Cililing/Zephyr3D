#ifndef MessageOut_h
#define MessageOut_h

#include "AbstractConnectors.h"

namespace zephyr::cbs {

template <typename M>
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

    template <
        typename T,
        typename CHECK = std::enable_if_t<std::is_same<M, typename std::decay_t<T>>::value>
    >
    void Send(T&& message);
};

}

#include "ConnectionsManager.h"

template <typename M>
template <
    typename T,
    typename CHECK
>
void zephyr::cbs::MessageOut<M>::Send(T&& message) {
    m_ConnectionsManager->ForwardMessage(*this, std::forward<T>(message));
}

#endif
