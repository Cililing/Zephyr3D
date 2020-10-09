#ifndef TriggerIn_h
#define TriggerIn_h

#include "AbstractConnectors.h"

template <class O, void(O::* F)()>
class TriggerIn final : public AbstractTriggerIn {
public:
    TriggerIn(O* owner)
        : AbstractTriggerIn(owner) {}

    TriggerIn() = delete;
    TriggerIn(const TriggerIn&) = delete;
    TriggerIn& operator=(const TriggerIn& other) = delete;
    TriggerIn(TriggerIn&&) = delete;
    TriggerIn& operator=(TriggerIn&&) = default;
    ~TriggerIn() = default;

    void Receive() override { (m_Owner->*F)(); }
};

#endif
