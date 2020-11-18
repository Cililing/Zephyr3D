#ifndef PropertyIn_h
#define PropertyIn_h

#include "AbstractConnectors.h"
#include "PropertyOut.h"

namespace zephyr::cbs {

template <class T>
class PropertyIn final : public AbstractPropertyIn {
public:
    PropertyIn(Component* owner)
        : AbstractPropertyIn(owner)
        , m_Source(nullptr) {

    }

    PropertyIn() = delete;
    PropertyIn(const PropertyIn&) = delete;
    PropertyIn& operator=(const PropertyIn& other) = delete;
    PropertyIn(PropertyIn&&) = delete;
    PropertyIn& operator=(PropertyIn&&) = delete;
    ~PropertyIn() = default;

    void RemoveSource() override { m_Source = nullptr; }

    const T& Value() const { return m_Source->Value(); }
    operator const T&() const { return m_Source->Value(); }
    const T* operator->() const { return &m_Source->Value(); }

    bool Connected() const { return m_Source != nullptr; }

    void Connect(PropertyOut<T>* source) { m_Source = source; }

private:
    PropertyOut<T>* m_Source;
};

}

#endif
