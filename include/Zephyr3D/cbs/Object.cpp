#include "Object.h"

#include "ObjectManager.h"
#include "../scenes/Scene.h"

Object::Object(ObjectManager& owner, ID_t id, std::string name)
    : m_ID(id)
    , m_Name(name)
    , m_Owner(owner)
    , m_ConnectionsManager()
    , m_NextCompID(2)
    , m_Root(*this, 1)
    , m_ToUpdate(0) 
    , m_ToInitializeNextFrame(0) {
    m_Root.Identity();
    
}

Object::~Object() {
    
}

void Object::InitializeComponents() {
    m_ToInitializeNextFrame = 0;
    m_Root.Initialize();
    for (auto& comp : m_Components) {
        comp->Initialize();
    }
}

void Object::ProcessFrame() {
    // Becuase either Initialize, Update or Destory functions can alter m_Components
    // use raw loop with indices instead of iterators

    // Initialize components
    Components_t::size_type iterator = m_Components.size() - m_ToInitializeNextFrame;
    m_ToInitializeNextFrame = 0;
    for (; iterator < m_Components.size(); iterator++) {
        m_Components[iterator]->Initialize();
    }

    // Update components
    iterator = m_MarkedToDestroy.size();
    for (; iterator < m_MarkedToDestroy.size() + m_ToUpdate; iterator++) {
        m_Components[iterator]->Update();
    }

    // Destroy components
    if (m_MarkedToDestroy.size() > 0) {
        // Prepare components to be erased by moving them at the end of m_Components
        std::remove_if(
            m_Components.begin(), 
            m_Components.end(), 
            [=](auto& it) { 
                return m_MarkedToDestroy.find(it->ID()) != m_MarkedToDestroy.end();
        });

        // Because Destroy function may add new components cache sizes
        // At this point all new components destruction will happen in a next frame
        auto destroy_count = m_MarkedToDestroy.size();
        auto components_count = m_Components.size();
        m_MarkedToDestroy.clear();

        for (int i = components_count - destroy_count; i < components_count; i++) {
            m_Components[i]->Destroy();
        }

        // Erase destroyed components but leave any new components
        m_Components.erase(m_Components.begin() + components_count - destroy_count, m_Components.begin() + components_count);
    }
}

void Object::DestroyComponents() {
    m_Root.Destroy();
    for (auto& comp : m_Components) {
        comp->Destroy();
    }
    m_ConnectionsManager.RemoveConnections();
}

void Object::RegisterUpdateCall(const Component* component) {
    assert(component->Object().ID() == m_ID);

    auto id = component->ID();
    Components_t::iterator comp = std::find_if(m_Components.begin(),
                                               m_Components.end(),
                                               [=](std::unique_ptr<Component>& curr) { return curr->ID() == id; });

    assert(comp != m_Components.end());
    m_ToUpdate += 1;
    /*if (std::distance(m_Components.begin() + m_ToDestroy, comp) >= static_cast<ptrdiff_t>(m_ToUpdate)) {
        std::iter_swap(m_Components.begin() + m_ToDestroy + m_ToUpdate, comp);
        m_ToUpdate += 1;
    }*/
}

void Object::UnregisterUpdateCall(const Component* component) {
    assert(component->Object().ID() == m_ID);

    auto id = component->ID();
    Components_t::iterator comp = std::find_if(m_Components.begin(),
                                               m_Components.end(),
                                               [=](std::unique_ptr<Component>& curr) { return curr->ID() == id; });

    assert(comp != m_Components.end());
    m_ToUpdate -= 1;
    /*if (std::distance(m_Components.begin() + m_ToDestroy, comp) <= static_cast<ptrdiff_t>(m_ToUpdate)) {
        std::iter_swap(m_Components.begin() + m_ToDestroy + m_ToUpdate, comp);
        m_ToUpdate -= 1;
    }*/
}

Scene& Object::Scene() const {
    return m_Owner.Scene();
}

void Object::RegisterConnector(Connector* connector) {
    m_ConnectionsManager.RegisterConnector(connector);
}

