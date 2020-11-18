#ifndef Component_h
#define Component_h

#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

namespace zephyr::cbs {

class Object;

/** \brief Base class for all components
 *
 * Components represents behaviour of game objects. To create new component inherit from this class and override
 * all neccesary functions. Each component has unique ID of type ID_t. 
 */
class Component {
public:
    using ID_t = int;

    Component(class Object& object, ID_t id);

    Component() = delete;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    Component(Component&&) = delete;
    Component& operator=(Component&&) = delete;
    virtual ~Component() = default;

    ID_t ID() const { return m_ID; }
    Object& Object() const { return m_Object; }

    virtual void Initialize() {};
    virtual void Update() {};
    virtual void Destroy() {};

protected:
    void RegisterUpdateCall() const;
    void UnregisterUpdateCall() const;

private:
    class Object& m_Object;
    ID_t m_ID;
};

}

#endif
