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

/*
#pragma region ForwardDeclarations

class Component;

class AbstractPropertyOut;
template <class T>
class PropertyOut;

class AbstractPropertyIn;
template <class T>
class PropertyIn;


class AbstractMessageOut;
template <class M>
class MessageOut;

class AbstractMessageIn;
template <class M, class O, void(O::* F)(M)>
class MessageIn;


class AbstractTriggerOut;
class TriggerOut;

class AbstractTriggerIn;
template <class O, void(O::*F)()>
class TriggerIn;

#pragma endregion
*/

/** \brief Manages all connection beetwen components inside one object
 *
 */
class ConnectionsManager {
    using PropertyConnections_t = std::vector<std::pair<AbstractPropertyOut*, AbstractPropertyIn*>>;
    using MessageConnections_t = std::unordered_map<AbstractMessageOut*, std::vector<AbstractMessageIn*>>;
    using TriggerConnections_t = std::unordered_map<AbstractTriggerOut*, std::vector<AbstractTriggerIn*>>;

public:
    void RegisterConnector(Connector* connector);

    template <class T>
    void Connect(PropertyOut<T>& subject, PropertyIn<T>& observer);

    template <class T>
    void Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer);

    template <class M, class O, void (O::*F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver);

    template <class M, class O, void (O::*F)(M)>
    void Disconnect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver);

    template <class O, void (O::* F)(void)>
    void Connect(TriggerOut& sender, TriggerIn<O, F>& receiver);

    template <class O, void (O::* F)(void)>
    void Disconnect(TriggerOut& sender, TriggerIn<O, F>& receiver);

    void ForwardMessage(AbstractMessageOut* sender, void* message);
    void ForwardTrigger(AbstractTriggerOut* sender);

    void RemoveConnections(Component* component);

private:
    std::unordered_map<Connector::ID_t, Connector*> m_Connectors;
    Connector::ID_t m_NextConnectorID = 0;

    PropertyConnections_t m_PropertyConnections;
    MessageConnections_t m_MessageConnections;
    TriggerConnections_t m_TriggerConnections;
};

template <class T>
void ConnectionsManager::Connect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
    if (observer.m_Source == nullptr) {
        observer.m_Source = &subject;

        m_PropertyConnections.emplace_back(&subject, &observer);
    } else {
        // TODO DebugLog
    }
}

template <class T>
void ConnectionsManager::Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
    m_PropertyConnections.erase(std::remove_if(m_PropertyConnections.begin(),
                                               m_PropertyConnections.end(),
                                               [=](std::pair<AbstractPropertyOut*, AbstractPropertyIn*>& pair) { 
                                                   if (pair.first == subject && pair.second == observer) {
                                                       pair.second->RemoveSource();
                                                       return true;
                                                   }
                                                   return false; }));
}

template <class M, class O, void(O::*F)(M)>
void ConnectionsManager::Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
    sender.m_ConnectionsManager = this;
    m_MessageConnections[&sender].push_back(&receiver);
}

template <class M, class O, void (O::*F)(M)>
void ConnectionsManager::Disconnect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
    m_MessageConnections[&sender].erase(std::remove(m_MessageConnections[&sender].begin(), 
                                                    m_MessageConnections[&sender].end(), 
                                                    receiver));
}

template <class O, void(O::* F)()>
void ConnectionsManager::Connect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
    sender.m_ConnectionsManager = this;
    m_TriggerConnections[&sender].push_back(&receiver);
}

template <class O, void(O::* F)()>
void ConnectionsManager::Disconnect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
    m_TriggerConnections[&sender].erase(std::remove(m_TriggerConnections[&sender].begin(),
                                                    m_TriggerConnections[&sender].end(),
                                                    receiver));
}

#endif
