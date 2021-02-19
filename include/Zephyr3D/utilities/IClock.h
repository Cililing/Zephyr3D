#ifndef IClock_h
#define IClock_h

namespace zephyr {

class IClock {
public:
    IClock() = default;
    IClock(const IClock&) = delete;
    IClock& operator=(const IClock&) = delete;
    IClock(IClock&&) = delete;
    IClock& operator=(IClock&&) = delete;
    virtual ~IClock() = default;

    virtual float CurrentTime() const = 0;
    virtual float DeltaTime() const = 0;
};

}

#endif
