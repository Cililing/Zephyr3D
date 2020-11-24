#ifndef ITimer_h
#define ITimer_h

namespace zephyr {

class ITimer {
public:
    ITimer() = default;
    ITimer(const ITimer&) = delete;
    ITimer& operator=(const ITimer&) = delete;
    ITimer(ITimer&&) = delete;
    ITimer& operator=(ITimer&&) = delete;
    virtual ~ITimer() = default;

    virtual float CurrentTime() const = 0;
    virtual float DeltaTime() const = 0;
};

}

#endif
