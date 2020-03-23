#ifndef Engine_h
#define Engine_h

class Engine {
public:
    static Engine& Instance() {
        static Engine instance;
        return instance;
    }

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

private:
    Engine() = default;
};

#endif
