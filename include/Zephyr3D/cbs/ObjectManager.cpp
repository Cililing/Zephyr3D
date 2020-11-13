#include "ObjectManager.h"

#include "../scenes/Scene.h"

ObjectManager::ObjectManager(class Scene& owner)
    : m_Scene(owner)
    , m_NextObjectID(0)
    , m_ToDestroy(0)
    , m_ToInitializeNextFrame(0) {
}

void ObjectManager::ProcessFrame() {
    Objects_t::size_type iterator = m_ToDestroy;
    for (; iterator < m_Objects.size() - m_ToInitializeNextFrame; iterator++) {
        m_Objects[iterator]->ProcessFrame();
    }
    m_ToInitializeNextFrame = 0;

    // Destroy components
    if (m_ToDestroy > 0) {
        m_Objects.erase(m_Objects.begin(), m_Objects.begin() + m_ToDestroy);
        m_ToDestroy = 0;
    }
}

void ObjectManager::DestroyObjects() {
    m_Objects.clear();
}

Object* ObjectManager::CreateObject(const std::string& name) {
    auto& obj = m_Objects.emplace_back(std::make_unique<Object>(*this, m_NextObjectID++, name));
    return obj.get();
}

void ObjectManager::DestroyObject(Object::ID_t id) {
    auto object = std::find_if(m_Objects.begin(),
                               m_Objects.end(),
                               [=](auto& it){ return it->ID() == id; });

    if (object != m_Objects.end() && std::distance(m_Objects.begin(), object) > static_cast<ptrdiff_t>(m_ToDestroy)) {
        std::iter_swap(m_Objects.begin() + m_ToDestroy, object);
        m_ToDestroy += 1;
    }
}
