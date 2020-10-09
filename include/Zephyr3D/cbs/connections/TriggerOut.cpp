#include "TriggerOut.h"
#include "ConnectionsManager.h"

void TriggerOut::Trigger() {
    if (m_ConnectionsManager) {
        m_ConnectionsManager->ForwardTrigger(this);
    }
}