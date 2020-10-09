#ifndef ConnectionInterfaces_h
#define ConnectionInterfaces_h

#include "Connector.h"

class AbstractPropertyOut : public Connector {
public:
    AbstractPropertyOut(Component* owner)
        : Connector(owner) {}

    AbstractPropertyOut(const AbstractPropertyOut&) = delete;
    AbstractPropertyOut& operator=(const AbstractPropertyOut&) = delete;
    AbstractPropertyOut(AbstractPropertyOut&&) = delete;
    AbstractPropertyOut& operator=(AbstractPropertyOut&&) = delete;
    virtual ~AbstractPropertyOut() = default;
};

class AbstractPropertyIn : public Connector {
public:
    AbstractPropertyIn(Component* owner)
        : Connector(owner) {}

    AbstractPropertyIn(const AbstractPropertyIn&) = delete;
    AbstractPropertyIn& operator=(const AbstractPropertyIn&) = delete;
    AbstractPropertyIn(AbstractPropertyIn&&) = delete;
    AbstractPropertyIn& operator=(AbstractPropertyIn&&) = delete;
    virtual ~AbstractPropertyIn() = default;

    virtual void RemoveSource() = 0;
};

class AbstractMessageOut : public Connector {
public:
    AbstractMessageOut(Component* owner)
        : Connector(owner) {}

    AbstractMessageOut(const AbstractMessageOut&) = delete;
    AbstractMessageOut& operator=(const AbstractMessageOut&) = delete;
    AbstractMessageOut(AbstractMessageOut&&) = delete;
    AbstractMessageOut& operator=(AbstractMessageOut&&) = delete;
    virtual ~AbstractMessageOut() = default;
};

class AbstractMessageIn : public Connector {
public:
    AbstractMessageIn(Component* owner)
        : Connector(owner) {}

    AbstractMessageIn(const AbstractMessageIn&) = delete;
    AbstractMessageIn& operator=(const AbstractMessageIn&) = delete;
    AbstractMessageIn(AbstractMessageIn&&) = delete;
    AbstractMessageIn& operator=(AbstractMessageIn&&) = delete;
    virtual ~AbstractMessageIn() = default;

    virtual void Receive(void* message) = 0;
};

class AbstractTriggerOut : public Connector {
public:
    AbstractTriggerOut(Component* owner)
        : Connector(owner) {}

    AbstractTriggerOut(const AbstractTriggerOut&) = delete;
    AbstractTriggerOut& operator=(const AbstractTriggerOut&) = delete;
    AbstractTriggerOut(AbstractTriggerOut&&) = delete;
    AbstractTriggerOut& operator=(AbstractTriggerOut&&) = delete;
    virtual ~AbstractTriggerOut() = default;

    virtual void Trigger() = 0;
};

class AbstractTriggerIn : public Connector {
public:
    AbstractTriggerIn(Component* owner)
        : Connector(owner) {}

    AbstractTriggerIn(const AbstractTriggerIn&) = delete;
    AbstractTriggerIn& operator=(const AbstractTriggerIn&) = delete;
    AbstractTriggerIn(AbstractTriggerIn&&) = delete;
    AbstractTriggerIn& operator=(AbstractTriggerIn&&) = delete;
    virtual ~AbstractTriggerIn() = default;

    virtual void Receive() = 0;
};

#endif
