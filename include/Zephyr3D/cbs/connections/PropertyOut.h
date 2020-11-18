#ifndef PropertyOut_h
#define PropertyOut_h

#include "AbstractConnectors.h"

namespace zephyr::cbs {

template <class T>
class PropertyOut final : public AbstractPropertyOut {
public:
    PropertyOut(Component* owner)
        : AbstractPropertyOut(owner) {
        m_Value = std::make_unique<T>();
    }

    template <class ...Args>
    PropertyOut(Component* owner, Args&& ...params)
        : AbstractPropertyOut(owner) {
        m_Value = std::make_unique<T>(params...);
    }

    PropertyOut() = delete;
    PropertyOut(const PropertyOut&) = delete;
    PropertyOut& operator=(const PropertyOut& other) = delete;
    PropertyOut(PropertyOut&&) = delete;
    PropertyOut& operator=(PropertyOut&&) = delete;
    ~PropertyOut() = default;

    T& operator=(const T& value) { return (*m_Value = value); }

    T& Value() { return *m_Value; }
    const T& Value() const { return *m_Value; }

    operator T&() { return *m_Value; }
    operator const T&() const { return *m_Value; }

private:
    std::unique_ptr<T> m_Value;
};

}

#endif
