#ifndef TestComponent_h
#define TestComponent_h

#include <Zephyr3D/cbs/components/Component.h>
#include <Zephyr3D/cbs/connections/MessageOut.h>
#include <Zephyr3D/cbs/connections/MessageIn.h>
#include <Zephyr3D/cbs/connections/PropertyIn.h>
#include <Zephyr3D/cbs/connections/PropertyOut.h>

class VocalClass {
public:
    VocalClass(int a) {
        std::cout << "Constructor\n";
        this->a = a;
    }

    VocalClass() {
        std::cout << "Default constructor\n";
    }
    ~VocalClass() {
        std::cout << "Destructor\n";
    }
    VocalClass(const VocalClass& rhs) {
        std::cout << "Copy constructor\n";
    }
    VocalClass& operator=(const VocalClass& rhs) {
        std::cout << "Copy operator\n";
    }
    VocalClass(VocalClass&& rhs) {
        std::cout << "Move constructor\n";
    }
    VocalClass& operator=(VocalClass&& rhs) {
        std::cout << "Move operator\n";
    }

    int a = 0;
};

class TestComponent : public Component {
public:

    void Initialize() override;
    void Update() override;

    void Foo(VocalClass vc) { std::cout << "received"; }

    MessageOut<VocalClass> out{this};
    MessageIn<VocalClass, TestComponent, &TestComponent::Foo> in{this};

    //PropertyOut<VocalClass> p_out{this, 5};
    //PropertyIn<VocalClass> p_in{this};
};



#endif // !TestComponent_h
