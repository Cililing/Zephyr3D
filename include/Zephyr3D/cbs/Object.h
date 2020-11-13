#ifndef Object_h
#define Object_h

#include "connections/ConnectionsManager.h"
#include "connections/MessageIn.h"
#include "connections/MessageOut.h"
#include "connections/PropertyIn.h"
#include "connections/PropertyOut.h"
#include "connections/TriggerIn.h"
#include "connections/TriggerOut.h"

#include "components/Component.h"
#include "components/Transform.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#pragma warning(pop)

#include <assert.h>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

class ObjectManager;
class Scene;

class Object {
    using Components_t = std::vector<std::unique_ptr<Component>>;

public:
    using ID_t = std::size_t;

    Object(ObjectManager& owner, ID_t id, std::string name);

    Object() = delete;
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
    Object(Object&&) = delete;
    Object& operator=(Object&&) = delete;
    ~Object();

    void InitializeComponents();
    void ProcessFrame();
    void DestroyComponents();

    void RegisterUpdateCall(const Component* component);
    void UnregisterUpdateCall(const Component* component);

    ID_t ID() const { return m_ID; }
    const std::string& Name() const { return m_Name; }
    Transform& Root() { return m_Root; }
    Scene& Scene() const;

    template <class T, typename ...Args>
    T* CreateComponent(Args&&... params) {
        auto& comp = m_Components.emplace_back(std::make_unique<T>(*this, m_NextCompID, params...));

        m_NextCompID++;
        m_ToInitializeNextFrame++;

        return dynamic_cast<T*>(comp.get());
    }

    template <class T>
    void RemoveComponents() {
        for (auto& comp : m_Components) {
            if (dynamic_cast<T*>(comp->get()) != nullptr) {
                auto result = m_MarkedToDestroy.insert(comp->ID());
                assert(result.second);
                UnregisterUpdateCall(comp->get());
            }
        }
    }

    void RemoveComponent(Component::ID_t id) {
        assert(id > 1);

        auto comp = std::find_if(m_Components.begin(),
                                 m_Components.end(),
                                 [=](std::unique_ptr<Component>& comp) { return comp->ID() == id; });

        // Mark to destroy
        if (comp != m_Components.end()) {
            auto result = m_MarkedToDestroy.insert(id);
            assert(result.second);
            UnregisterUpdateCall(comp->get());
        }
    }

    template <class T>
    std::vector<T*> GetComponents() {
        std::vector<T*> comps;

        for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
            if (auto comp = dynamic_cast<T*>(it->get())) {
                comps.push_back(comp);
            }
        }

        return comps;
    }

    template <class T>
    T* GetComponent(Component::ID_t id) {
        Components_t::iterator it = std::find_if(m_Components.begin(),
                               m_Components.end(),
                               [=](std::unique_ptr<Component>& curr) { return curr->ID() == id; });

        if (it != m_Components.end()) {
            return dynamic_cast<T*>(it->get());
        } else {
            return nullptr;
        }
    }

    void RegisterConnector(Connector* connector);

    template <class T>
    void Connect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
        assert(subject.Owner()->Object().ID() == m_ID && observer.Owner()->Object().ID() == m_ID);
        m_ConnectionsManager.Connect(subject, observer);
    }

    template <class M, class O, void(O::* F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
        assert(sender.Owner()->Object().ID() == m_ID && receiver.Owner()->Object().ID() == m_ID);
        m_ConnectionsManager.Connect(sender, receiver);
    }

    template <class O, void(O::*F)(void)>
    void Connect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
        assert(sender.Owner()->Object().ID() == m_ID && receiver.Owner()->Object().ID() == m_ID);
        m_ConnectionsManager.Connect(sender, receiver);
    }

    template <class T>
    void Disconnect(PropertyIn<T>& observer) {
        assert(observer.Owner()->Object().ID() == m_ID);
        m_ConnectionsManager.Disconnect(observer);
    }

    template <class M, class O, void (O::*F)(M)>
    void Disconnect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
        assert(sender.Owner()->Object().ID() == m_ID && receiver.Owner()->Object().ID() == m_ID);
        m_ConnectionsManager.Disconnect(sender, receiver);
    }

    template <class O, void (O::*F)(void)>
    void Disconnect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
        assert(sender.Owner()->Object().ID() == m_ID && receiver.Owner()->Object().ID() == m_ID);
        m_ConnectionsManager.Disconnect(sender, receiver);
    }

private:
    ID_t m_ID;
    std::string m_Name;
    ObjectManager& m_Owner;
    ConnectionsManager m_ConnectionsManager;

    Transform m_Root;
    Components_t m_Components;
    Components_t::size_type m_ToUpdate;
    Components_t::size_type m_ToInitializeNextFrame;
    std::set<Component::ID_t> m_MarkedToDestroy;

    Component::ID_t m_NextCompID;
};

#endif
