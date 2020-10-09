#include "TriggerOut.h"
#include "ConnectionsManager.h"

void TriggerOut::Trigger() {
    m_ConnectionsManager->ForwadTrigger(*this);
}

