#include "TriggerOut.h"
#include "ConnectionsManager.h"

void zephyr::cbs::TriggerOut::Trigger() {
    m_ConnectionsManager->ForwadTrigger(*this);
}

