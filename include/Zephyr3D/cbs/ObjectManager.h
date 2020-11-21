#ifndef ObjectManager_h
#define ObjectManager_h

#include "IObjectManager.h"
#include "Object.h"

#include <vector>
#include <set>
#include <string>
#include <algorithm>

namespace zephyr {
class Scene;
}

namespace zephyr::cbs {

class ObjectManager : public IObjectManager {
    using Objects_t = std::vector<std::unique_ptr<Object>>;

public:
    explicit ObjectManager(class Scene& owner);

    Object* CreateObject(const std::string& name);
    void DestroyObject(Object::ID_t id);

    void InitializeObjects();
    void ProcessFrame();
    void DestroyObjects();

    Scene& Scene() const { return m_Scene; }
    Object* Object(Object::ID_t id) const;

private:
    class Scene& m_Scene;

    Object::ID_t m_NextObjectID;

    Objects_t m_Objects;
    Objects_t::size_type m_ToInitializeNextFrame;
    std::set<Object::ID_t> m_MarkedToDestroy;
};

}

#endif
