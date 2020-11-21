#ifndef IObjectManager_h
#define IObjectManager_h

namespace zephyr::cbs {

class IObjectManager {
public:
    IObjectManager() = default;
    IObjectManager(const IObjectManager&) = delete;
    IObjectManager& operator=(const IObjectManager&) = delete;
    IObjectManager(IObjectManager&&) = delete;
    IObjectManager& operator=(IObjectManager&&) = delete;
    virtual ~IObjectManager() = default;
};

}

#endif 
