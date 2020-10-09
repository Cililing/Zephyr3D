#ifndef Component_h
#define Component_h

#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

class Object;

/** \brief Base class for all components
 *
 * Components represents behaviour of game objects. To create new component inherit from this class and override
 * all neccesary functions. Each component has unique ID of type ID_t. 
 */
class Component {
    friend class Object;

public:
    using ID_t = int;

    Component(class Object& object, ID_t id);

    Component() = delete;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    Component(Component&&) = delete;
    Component& operator=(Component&&) = delete;
    virtual ~Component() = default;

    /// Returns component ID
    ID_t ID() const { return m_ID; }

    /// Returns component owner
    Object& Object() const { return m_Object; }

protected:
    virtual void Initialize() {};
    virtual void Update() {};
    virtual void Destroy() {};

    void RegisterUpdateCall() const;
    void UnregisterUpdateCall() const;

private:
    class Object& m_Object;
    ID_t m_ID;
};

#endif
