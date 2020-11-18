#ifndef ConnectionsManager_h
#define ConnectionsManager_h

#include "Connector.h"
#include "MessageIn.h"
#include "MessageOut.h"
#include "PropertyIn.h"
#include "PropertyOut.h"
#include "TriggerIn.h"
#include "TriggerOut.h"

#include <algorithm>
#include <vector>
#include <unordered_map>

namespace zephyr::cbs {

class ConnectionsManager {
    using PropertyConnections_t = std::vector<std::pair<AbstractPropertyOut*, AbstractPropertyIn*>>;
    using MessageConnections_t = std::unordered_map<AbstractMessageOut*, std::vector<AbstractMessageIn*>>;
    using TriggerConnections_t = std::unordered_map<AbstractTriggerOut*, std::vector<AbstractTriggerIn*>>;

public:
    void RegisterConnector(Connector* connector);

    template <class T>
    void Connect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
        observer.Connect(&subject);
        m_PropertyConnections.emplace_back(&subject, &observer);
    }

    template <class T>
    void Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
        observer.Connect(nullptr);
        auto to_remove = std::make_pair(subject, observer);
        m_PropertyConnections.erase(std::remove(m_PropertyConnections.begin(),
                                                m_PropertyConnections.end(),
                                                to_remove));
    }

    template <class M, class O, void (O::*F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
        m_MessageConnections[&sender].push_back(&receiver);
    }

    template <class M, class O, void (O::*F)(M)>
    void Disconnect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
        auto& receivers = m_MessageConnections[&sender];
        receivers.erase(std::remove(receivers.begin(),
                                    receivers.end(),
                                    receiver));
    }

    template <class O, void (O::* F)(void)>
    void Connect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
        m_TriggerConnections[&sender].push_back(&receiver);
    }

    template <class O, void (O::* F)(void)>
    void Disconnect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
        auto& receivers = m_TriggerConnections[&sender];
        receivers.erase(std::remove(receivers.begin(),
                                    receivers.end(),
                                    receiver));
    }

    template <class T>
    void ForwardMessage(AbstractMessageOut& sender, T&& message);
    void ForwadTrigger(AbstractTriggerOut& sender);

    void RemoveConnections();
    void RemoveConnections(Component* component);

private:
    PropertyConnections_t m_PropertyConnections;
    MessageConnections_t m_MessageConnections;
    TriggerConnections_t m_TriggerConnections;
    Connector::ID_t m_NextConnectorID = 0;
};

template <class T>
void ConnectionsManager::ForwardMessage(AbstractMessageOut& sender, T&& message) {
    for (auto it : m_MessageConnections[&sender]) {
        it->Receive(&message);
    }
}

}

#endif
