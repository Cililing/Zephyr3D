#ifndef MessageIn_h
#define MessageIn_h

#include "AbstractConnectors.h"

namespace zephyr::cbs {

template <class M, class O, void(O::*F)(M)>
class MessageIn final : public AbstractMessageIn {
public:
    MessageIn(O* owner)
        : AbstractMessageIn(owner) {

    }

    MessageIn() = delete;
    MessageIn(const MessageIn&) = delete;
    MessageIn& operator=(const MessageIn& other) = delete;
    MessageIn(MessageIn&&) = delete;
    MessageIn& operator=(MessageIn&&) = delete;
    ~MessageIn() = default;

    void Receive(void* message) override { (dynamic_cast<O*>(m_Owner)->*F)(*static_cast<M*>(message)); }
};

}

#endif
