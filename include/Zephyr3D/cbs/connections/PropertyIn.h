#ifndef PropertyIn_h
#define PropertyIn_h

#include "AbstractConnectors.h"
#include "PropertyOut.h"

class ConnectionsManager;

template <class T>
class PropertyIn final : public AbstractPropertyIn {
    friend class ConnectionsManager;

public:
    PropertyIn(Component* owner)
        : AbstractPropertyIn(owner)
        , m_Source(nullptr) {}

    PropertyIn() = delete;
    PropertyIn(const PropertyIn&) = delete;
    PropertyIn& operator=(const PropertyIn& other) = delete;
    PropertyIn(PropertyIn&&) = delete;
    PropertyIn& operator=(PropertyIn&&) = delete;
    ~PropertyIn() = default;

    const T& Value() const { return m_Source->Value(); }
    operator const T&() const { return m_Source->Value(); }

    const T* operator->() const { return &m_Source->Value(); }

    bool Connected() const { return m_Source != nullptr; }

private:
    void RemoveSource() override { m_Source = nullptr; }

    PropertyOut<T>* m_Source;
};


#endif
