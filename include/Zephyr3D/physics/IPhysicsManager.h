#ifndef IPhysicsManager_h
#define IPhysicsManager_h

namespace zephyr::physics {

class IPhysicsManager {
public:
    IPhysicsManager() = default;
    IPhysicsManager(const IPhysicsManager&) = delete;
    IPhysicsManager& operator=(const IPhysicsManager&) = delete;
    IPhysicsManager(IPhysicsManager&&) = delete;
    IPhysicsManager& operator=(IPhysicsManager&&) = delete;
    virtual ~IPhysicsManager() = default;
};

}

#endif
