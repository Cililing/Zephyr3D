#include "ConnectionsManager.h"

#include "../components/Component.h"

void ConnectionsManager::RegisterConnector(Connector* connector) {
    connector->m_ID = m_NextConnectorID;
    connector->m_ConnectionsManager = this;
    m_NextConnectorID++;
}

void ConnectionsManager::ForwadTrigger(AbstractTriggerOut& sender) {
    for (auto it : m_TriggerConnections[&sender]) {
        it->Receive();
    }
}

void ConnectionsManager::RemoveConnections(Component* component) {
    auto comp_id = component->ID();

    //
    m_PropertyConnections.erase(std::remove_if(m_PropertyConnections.begin(),
                                               m_PropertyConnections.end(),
                                               [=](auto conn) {
                                                    if (conn.first->Owner()->ID() == comp_id) {
                                                        conn.second->RemoveSource();
                                                        return true;
                                                    }

                                                    return conn.second->Owner()->ID() == comp_id;
                                               }),
                                m_PropertyConnections.end());

    //
    for (auto it = m_MessageConnections.begin(); it != m_MessageConnections.end(); ) {
        if (it->first->Owner()->ID() == comp_id) {
            m_MessageConnections.erase(it++);
        }
        else {
            it->second.erase(std::remove_if(it->second.begin(),
                                            it->second.end(),
                                            [=](auto receiver) { return receiver->Owner()->ID() == comp_id; }),
                             it->second.end());
            it++;
        }
    }

    //
    for (auto it = m_TriggerConnections.begin(); it != m_TriggerConnections.end(); ) {
        if (it->first->Owner()->ID() == comp_id) {
            m_TriggerConnections.erase(it++);
        }
        else {
            it->second.erase(std::remove_if(it->second.begin(),
                                            it->second.end(),
                                            [=](auto receiver) { return receiver->Owner()->ID() == comp_id; }),
                             it->second.end());
            it++;
        }
    }
}
