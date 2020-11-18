#ifndef TriggerOut_h
#define TriggerOut_h

#include "AbstractConnectors.h"

namespace zephyr::cbs {

class TriggerOut final : public AbstractTriggerOut {
public:
    TriggerOut(Component* owner)
        : AbstractTriggerOut(owner) {

    }

    TriggerOut(const TriggerOut&) = delete;
    TriggerOut& operator=(const TriggerOut& other) = delete;
    TriggerOut(TriggerOut&&) = delete;
    TriggerOut& operator=(TriggerOut&&) = delete;
    ~TriggerOut() = default;

    void Trigger() override;
};

}

#endif
