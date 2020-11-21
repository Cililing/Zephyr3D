#ifndef IDrawManager_h
#define IDrawManager_h

namespace zephyr::rendering {

class IDrawManager {
public:
    IDrawManager() = default;
    IDrawManager(const IDrawManager&) = delete;
    IDrawManager& operator=(const IDrawManager&) = delete;
    IDrawManager(IDrawManager&&) = delete;
    IDrawManager& operator=(IDrawManager&&) = delete;
    virtual ~IDrawManager() = default;
};

}

#endif

