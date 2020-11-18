#include "ObjectManager.h"

#include "../scenes/Scene.h"

zephyr::cbs::ObjectManager::ObjectManager(class Scene& owner)
    : m_Scene(owner)
    , m_NextObjectID(0)
    , m_ToInitializeNextFrame(0) {
}

zephyr::cbs::Object* zephyr::cbs::ObjectManager::CreateObject(const std::string& name) {
    auto& obj = m_Objects.emplace_back(std::make_unique<class Object>(*this, m_NextObjectID, name));

    m_NextObjectID++;
    m_ToInitializeNextFrame++;

    return obj.get();
}

void zephyr::cbs::ObjectManager::DestroyObject(Object::ID_t id) {
    auto object = std::find_if(m_Objects.begin(),
                               m_Objects.end(),
                               [=](auto& it) { return it->ID() == id; });

    assert(object != m_Objects.end());
    auto result = m_MarkedToDestroy.insert(id);
    assert(result.second);
}


void zephyr::cbs::ObjectManager::InitializeObjects() {
    for (int i = 0; i < m_Objects.size(); i++) {
        m_Objects[i]->InitializeComponents();
    }
}

void zephyr::cbs::ObjectManager::ProcessFrame() {
    Objects_t::size_type iterator = m_Objects.size() - m_ToInitializeNextFrame;
    m_ToInitializeNextFrame = 0;
    for (; iterator < m_Objects.size(); iterator++) {
        m_Objects[iterator]->InitializeComponents();
    }

    iterator = m_MarkedToDestroy.size();
    for (; iterator < m_Objects.size() - m_ToInitializeNextFrame; iterator++) {
        m_Objects[iterator]->ProcessFrame();
    }

    if (m_MarkedToDestroy.size() > 0) {
        std::remove_if(m_Objects.begin(),
                       m_Objects.end(),
                       [=](auto& it) { return m_MarkedToDestroy.find(it->ID()) != m_MarkedToDestroy.end(); });

        auto destroy_count = m_MarkedToDestroy.size();
        auto objects_count = m_Objects.size();
        m_MarkedToDestroy.clear();

        for (int i = objects_count - destroy_count; i < objects_count; i++) {
            m_Objects[i]->DestroyComponents();
        }

        m_Objects.erase(m_Objects.begin() + objects_count - destroy_count, m_Objects.begin() + objects_count);
    }
}

void zephyr::cbs::ObjectManager::DestroyObjects() {
    for (int i = 0; i < m_Objects.size(); i++) {
        m_Objects[i]->DestroyComponents();
    }
    m_Objects.clear();
}

zephyr::cbs::Object* zephyr::cbs::ObjectManager::Object(Object::ID_t id) const {
    auto res = std::find_if(m_Objects.begin(),
                            m_Objects.end(),
                            [=](auto& obj) { return obj->ID() == id; });

    assert(m_MarkedToDestroy.find((*res)->ID()) != m_MarkedToDestroy.end());
    return res->get();
}

